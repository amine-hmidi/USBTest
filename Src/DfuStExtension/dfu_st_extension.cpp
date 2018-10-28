/* ******************************************************************************* */
/* ******************************** Copyright (C) ******************************** */
/* ******************************************************************************* */
/*                                                                                 */
/* This file is part of USBTest Suite.                                             */
/*                                                                                 */
/* USBTest Suite is free software; you can redistribute it and/or                  */
/* modify it under the terms of the GNU General Public License                     */
/* as published by the Free Software Foundation; either version 2                  */
/* of the License, or (at your option) any later version.                          */
/*                                                                                 */
/* USBTest Suite is distributed in the hope that it will be useful,                */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of                  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   */
/* GNU General Public License for more details.                                    */
/*                                                                                 */
/* You should have received a copy of the GNU General Public License               */
/* along with USBTest Suite; if not, write to the Free Software                    */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */
/*                                                                                 */
/* Copyright (C) 2018  Amine Hmidi (amine.hmidi0.1@gmail.com)                      */
/*                                                                                 */
/* ******************************************************************************* */


/* C++ Includes */
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>

/* C Includes */

/* User Includes */
#include "dfu_st_extension.h"
#ifdef __linux__
#include <unistd.h>
#elif WIN32
#include <windows.h>
#endif


/**
 * @brief DFUClass::DFUClass
 * @param vendor_id
 * @param product_id
 */
DFUSE::DFUSE() : DFUClass(0x483, 0xdf11)
{
    /* check device class */
    this->usb_class = StandardUSB::USBClassType::DFU_ST_EX;
}


/**
 * @brief DFUClass::~DFUClass
 */
DFUSE::~DFUSE()
{
    this->DFUClass::CloseDevice();
}


/* ********************************************************************************************** */
/* **************************** Device Handling/Discovering Functions *************************** */
/* ********************************************************************************************** */
/**
 * @brief DFUSE::OpenDevice
 * Open the device as a standard usb device, search for the dfu interface and the dfu functional
 * descriptor interface and check the bcdDFUVersion
 * @return 0 on success, -1 otherwise
 */
int8_t DFUSE::OpenDevice()
{
    if (this->DFUClass::OpenDevice())
        return -1;

    if (this->dfu_func_desc.bcdDFUVersion != 0x11a)
        return -1;

    return 0;
}


/**
 * @brief DFUSE::CloseDevice
 * @return 0 allways
 */
int8_t DFUSE::CloseDevice()
{
    return this->DFUClass::CloseDevice();
}


/**
 * @brief DFUSE::ReOpenDevice
 * @return 0 on success, -1 otherwise
 */
int8_t DFUSE::ReOpenDevice()
{
    this->CloseDevice();
    return this->OpenDevice();
}


/* ****************************************************************************************** */
/* ************************************** DFUSE Requests ************************************ */
/* ****************************************************************************************** */

int8_t DFUSE::DfuseGetCommand(uint8_t *data, uint16_t length)
{
    int result = this->DfuUploadPacket(0x00, data, length);
    if (result < 0)
    {
        return static_cast<int8_t>(result);
    }

    return  0;
}


int8_t DFUSE::DfuSeSetAddress(uint32_t address)
{
    uint8_t data[5] = {
        0x21,
        static_cast<uint8_t>(address & 0xFF),
        static_cast<uint8_t>((address >> 8) & 0xFF),
        static_cast<uint8_t>((address >> 16) & 0xFF),
        static_cast<uint8_t>((address >> 24) & 0xFF)
    };

    int result = this->DfuDownloadPacket(0x00, data, 5);
    if (result < 0)
        return static_cast<int8_t>(result);
    return  0;
}


int8_t DFUSE::DfuSeEraseSector(uint32_t address)
{
    uint8_t data[5] = {
        0x41,
        static_cast<uint8_t>(address & 0xFF),
        static_cast<uint8_t>((address >> 8) & 0xFF),
        static_cast<uint8_t>((address >> 16) & 0xFF),
        static_cast<uint8_t>((address >> 24) & 0xFF)
    };

    int result = this->DfuDownloadPacket(0x00, data, 5);
    if (result < 0)
        return static_cast<int8_t>(result);
    return  0;
}


int8_t DFUSE::DfuSeMassErase()
{
    uint8_t data[1] = {0x41};

    int result = this->DfuDownloadPacket(0x00, data, 1);
    if (result < 0)
        return static_cast<int8_t>(result);
    return  0;
}


int8_t DFUSE::DfuSeReadUnprotect()
{
    uint8_t data[1] = {0x92};

    /* check that the device is in the right state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
        (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if((this->dfu_state != dfuDNLOAD_IDLE) && (this->dfu_state != dfuIDLE))
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in the right state (" + GetStateStr(this->dfu_state)
                             + ") to send Download command, Download command will be sent anyway");
    }

    /* Send Buffer */
    int result = this->USBControlTransfer(
                     /* bmRequestType */     DFU_REQUEST_OUT,
                     /* bRequest      */     DFU_DNLOAD,
                     /* wValue        */     0x00,
                     /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                     /* data          */     const_cast<uint8_t *>(data),
                     /* length        */     1);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU Download request, "  + GetStrError(result));
        return static_cast<int8_t>(result);
    }

    if (result != 1)
    {
        std::stringstream stream;
        stream << "Error while sending DFU Download request, Device only received 0x"
               << std::setw(4) << static_cast<uint32_t>(result) << " bytes out of 0x"
               << std::setw(4) << static_cast<uint32_t>(result) << " bytes";
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, stream.str());
        return -99;
    }

    /* check that the device is in the right state */
    int retry = 100;
    DfuGetState();
    while ((this->dfu_state == DFUClass::DFUState::stateUNKNOWN) && retry)
    {
        DfuGetState();
        --retry;
    }

    if ((this->dfu_state == DFUClass::DFUState::stateUNKNOWN) && !retry)
    {
        return -99;
    }

    if(this->dfu_state != DFUClass::DFUState::dfuDNLOAD_SYNC)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuDNLOAD_SYNC, after Download "
                             "Command, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    /* Send the First Get Status */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) &&
        (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    /* donwload complete */
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::OK) &&
        (this->dfu_status.bState == DFUClass::DFUState::dfuDNLOAD_IDLE))
    {
        return static_cast<int8_t>(result);
    }

    if (this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Download Command's "
                             "Get Status, (" + GetStatusStr(this->dfu_status.bStatus) + ")");
        return -99;
    }

    if (this->dfu_state != DFUClass::DFUState::dfuDNLOAD_SYNC &&
        this->dfu_state != DFUClass::DFUState::dfuDNBUSY)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuDNLOAD_SYNC/dfuDNBUSY, after "
                             "Download Command's Get Status, (" + GetStateStr(this->dfu_state) +
                             ")");
        return -99;
    }

    /* Give the device some time to reconnect */
#ifdef __linux__
    usleep(1000 * 1000);
#elif WIN32
    Sleep(1000);
#endif
    /* Reconnect the device */
    result = this->ReOpenDevice();
    if (result)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to reconnect to target device after DFUSE Read Unprotect");
        return static_cast<int8_t>(result);
    }
    return  0;
}
