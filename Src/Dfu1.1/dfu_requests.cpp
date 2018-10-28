/* ******************************************************************************* */
/* ******************************** Copyright (C) ******************************** */
/* ******************************************************************************* */
/*                                                                                 */
/* This file is part of USBTest.                                                   */
/*                                                                                 */
/* USBTest is free software; you can redistribute it and/or                        */
/* modify it under the terms of the GNU General Public License                     */
/* as published by the Free Software Foundation; either version 2                  */
/* of the License, or (at your option) any later version.                          */
/*                                                                                 */
/* USBTest is distributed in the hope that it will be useful,                      */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of                  */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                   */
/* GNU General Public License for more details.                                    */
/*                                                                                 */
/* You should have received a copy of the GNU General Public License               */
/* along with USBTest; if not, write to the Free Software                          */
/* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA. */
/*                                                                                 */
/* Copyright (C) 2018  Amine Hmidi (amine.hmidi0.1@gmail.com)                      */
/*                                                                                 */
/* ******************************************************************************* */


/* C++ Includes */
#include <iostream>
#include <iomanip>
#include <sstream>

/* C Includes */

/* User Includes */
#include "dfu_class.h"
#include <libusb-1.0/libusb.h>
#ifdef __linux__
#include <unistd.h>
#elif WIN32
#include <windows.h>
#endif

/* ********************************************************************************************** */
/* *************************************** DFU1.1 Requests ************************************** */
/* ********************************************************************************************** */
/**
 * @brief DFUClass::DfuGetStatus
 * The host employs the DFU_GETSTATUS request to facilitate synchronization with the device.
 * @return a const DFUClass::Status struct
 */
const DFUClass::Status DFUClass::DfuGetStatus()
{
    /* wait for the PollTimeout */
#ifdef __linux__
    usleep(1000 * this->dfu_status.bwPollTimeOut);
#elif WIN32
    Sleep(this->dfu_status.bwPollTimeOut);
#endif

    this->dfu_status.Clear();
    uint8_t data[6] = {0x00};
    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_IN,
                 /* bRequest      */     DFU_GETSTATUS,
                 /* wValue        */     0x00,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     data,
                 /* length        */     0x06);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Get DFU device Status, "  + this->GetStrError(result));
        return this->dfu_status;
    }

    if (result < 6)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Get DFU device Status, Recieved Bytes number is less than"
                             " 0x06");
        return this->dfu_status;
    }

    this->dfu_status.bStatus = static_cast<DFUClass::DFUStatus>(data[0]);
    this->dfu_status.bwPollTimeOut = (data[1] | (static_cast<uint32_t>(data[2]) << 8) |
            (static_cast<uint32_t>(data[3]) << 16));
    this->dfu_status.bState = static_cast<DFUClass::DFUState>(data[4]);
    this->dfu_status.iString = data[5];

    this->dfu_state = static_cast<DFUClass::DFUState>(data[4]);

    return this->dfu_status;
}


/**
 * @brief DFUClass::DfuGetState
 * This request solicits a report about the state of the device. The state reported is the current
 * state of the device with no change in state upon transmission of the response. The values
 * specified in the bState field are identical to those reported in DFU_GETSTATUS.
 * @return a DFUClass::DFUState
 */
DFUClass::DFUState DFUClass::DfuGetState()
{
    uint8_t data[1] = {0x00};
    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_IN,
                 /* bRequest      */     DFU_GETSTATE,
                 /* wValue        */     0x00,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     data,
                 /* length        */     0x01);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Get DFU device State, " + GetStrError(result));
        return DFUState::stateUNKNOWN;
    }

    if (result != 1)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Get DFU device State, Recieved Bytes number is different "
                             "from 0x01");
        return DFUState::stateUNKNOWN;
    }

    this->dfu_state = static_cast<DFUClass::DFUState>(data[0]);

    return this->dfu_state;
}


/**
 * @brief DFUClass::DfuClearStatus
 * Any time the device detects an error and reports an error indication status to the host in the
 * response to a DFU_GETSTATUS request, it enters the dfuERROR state. The device cannot transition
 * from the dfuERROR state, after reporting any error status, until after it has received a
 * DFU_CLRSTATUS request. Upon receipt of DFU_CLRSTATUS, the device sets a status of OK and
 * transitions to the dfuIDLE state. Only then is it able to transition to other states
 * @return 0 on success, negative integer otherwise
 */
int DFUClass::DfuClearStatus()
{
    /* check that the device is in dfuERROR state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if(this->dfu_state != DFUClass::DFUState::dfuERROR)
    {
        std::stringstream stream;

        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in dfuERROR state (" + GetStateStr(this->dfu_state)
                             + "), Clear Status command will be sent anyway");
    }

    /* Send Clear Status Command */
    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_OUT,
                 /* bRequest      */     DFU_CLRSTATUS,
                 /* wValue        */     0x00,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     nullptr,
                 /* length        */     0x00);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU device Clear Status, " + GetStrError(result));
        return result;
    }

    /* check that the device is in dfuIDLE state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if(this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Clear Status Command, "
                             "(" + GetStatusStr(this->dfu_status.bStatus));
        return -99;
    }

    if(this->dfu_state != DFUClass::DFUState::dfuIDLE)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuIDLE, after Clear Status "
                             "Command, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    return result;
}


/**
 * @brief DFUClass::DfuAbort
 * The DFU_ABORT request enables the host to exit from certain states and return to the DFU_IDLE
 * state. The device sets the OK status on receipt of this request.
 * @return 0 on success, negative ninteger otherwise
 */
int DFUClass::DfuAbort()
{
    /* check that the device is in the right state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if ((this->dfu_state != dfuIDLE) && (this->dfu_state != dfuDNLOAD_SYNC) &&
        (this->dfu_state != dfuDNLOAD_IDLE) && (this->dfu_state != dfuMANIFEST_SYNC) &&
        (this->dfu_state != dfuUPLOAD_IDLE))
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in the right state (" + GetStateStr(this->dfu_state)
                             + ") to send Abort command, Abort command will be sent anyway");
    }

    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_OUT,
                 /* bRequest      */     DFU_ABORT,
                 /* wValue        */     0x00,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     nullptr,
                 /* length        */     0x00);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU device Abort, "  + GetStrError(result));
        return result;
    }

    /* check that the device is in dfuIDLE state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if(this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Abort Command, ("
                             + GetStatusStr(this->dfu_status.bStatus));
        return -99;
    }

    if(this->dfu_state != DFUClass::DFUState::dfuIDLE)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuIDLE, after Abort Command, ("
                             + GetStateStr(this->dfu_state));
        return -99;
    }

    return result;
}


/**
 * @brief DFUClass::DfuDetach
 * This command is used in the reconfiguration phase. The host and the device must negotiate to
 * perform the upgrade: the host issues a DETACH request and proceeds with a USB port reset, than
 * the device enumerates the DFU descriptor set.
 * @return 0 on success, a negative number otherwise
 */
int DFUClass::DfuDetach()
{
    /* check that the device is in the right state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if (this->dfu_state != appIDLE)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in the right state (" + GetStateStr(this->dfu_state)
                             + ") to send DETACH command, DETACH command will be sent anyway");
    }

    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_OUT,
                 /* bRequest      */     DFU_DETACH,
                 /* wValue        */     this->wDetachTimeOut,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     nullptr,
                 /* length        */     0x00 );

    if (result)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU DETACH request, "  + GetStrError(result));
        return result;
    }

    /* Send USB reset Command */
    if (!will_detach)
    {
        this->USBReset();
    }

    /* Give the device some time to reconnect */
#ifdef __linux__
    usleep(1000 * 1000);
#elif WIN32
    Sleep(1000);
#endif
    /* Reconnect the device in case of descriptor change
     * asuming that the device will keep the same idProduct */
    result = this->ReOpenDevice();
    if (result)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to reconnect to target device after DFU DETACH request");
        return result;
    }

    /* check that the device is in dfuIDLE state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if(this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after DETACH Command, ("
                             + GetStatusStr(this->dfu_status.bStatus));
        return -99;
    }

    if(this->dfu_state != DFUClass::DFUState::appDETACH)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: appDETACH, after DETACH Command, "
                             "(" + GetStateStr(this->dfu_state));
        return -99;
    }

    return result;
}


/**
 * @brief DFUClass::DfuDownloadPacket
 * The firmware image is downloaded via control-write transfers initiated by the DFU_DNLOAD class
 * specific request. The device specifies the maximum number of bytes per transfer via the
 * wTransferSize field of the functional descriptor. The host sends between bMaxPacketSize0 and
 * wTransferSize bytes to the device in a control-write transfer. Following each downloaded block,
 * the host solicits the device status with the DFU_GETSTATUS request.
 * @param wBlockNum the Packet number to be downloaded
 * @param data the data buffer to be downloaded
 * @param length the data buffer length ( <= wTransferSize)
 * @return the number of transfered data on success, a negative integer otherwise
 */
int DFUClass::DfuDownloadPacket(uint16_t wBlockNum, const uint8_t *data, uint16_t length)
{
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
                 /* wValue        */     wBlockNum,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     const_cast<uint8_t *>(data),
                 /* length        */     length);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU Download request, "  + GetStrError(result));
        return result;
    }

    if (result != length)
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
        return result;
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
                             "Download Command's Get Status, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    /* download buzy or synchronize */
    /* Send the Second Get Status */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if (this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Download Command 2nd "
                             "Get Status, (" + GetStatusStr(this->dfu_status.bStatus) + ")");
        return -99;
    }

    if (this->dfu_state != DFUClass::DFUState::dfuDNLOAD_IDLE)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuDNLOAD_IDLE, after Download "
                             "Command 2nd Get Status, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    return result;
}


/**
 * @brief DFUClass::DfuDownloadZero
 * After the final block of firmware has been sent to the device and the status solicited, the host
 * sends a DFU_DNLOAD request with the wLength field cleared to 0 and then solicits the status
 * again. If the result indicates that the device is ready and there are no errors, then the
 * Transfer phase is complete and the Manifestation phase begins
 * @param wBlockNum the final Packet index
 * @return 0 on success, a negative integer otherwise
 */
int DFUClass::DfuDownloadZero(uint16_t wBlockNum)
{
    /* check that the device is in the right state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if (((this->dfu_state != dfuDNLOAD_IDLE)
#if defined (USB_DFU_STEXTENSION)
         && (this->usb_class == USBClassType::DFU_1_1))
        || ((this->usb_class == USBClassType::DFU_ST_EX) && (this->dfu_state != dfuDNLOAD_IDLE)
            && (this->dfu_state != dfuIDLE)
#endif
        ))
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in the right state (" + GetStateStr(this->dfu_state)
                             + ")to send Download with Zero Length command, Download command will "
                               "be sent anyway");
    }

    /* Send Buffer */
    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_OUT,
                 /* bRequest      */     DFU_DNLOAD,
                 /* wValue        */     wBlockNum,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     nullptr,
                 /* length        */     0x00);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU Download request, "  + GetStrError(result));
        return result;
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

    if(this->dfu_state != DFUClass::DFUState::dfuMANIFEST_SYNC)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuMANIFEST_SYNC, after Download "
                             "Zero Length Command, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    /* Send the First Get Status */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if (this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Download Zero Length "
                             "Command Get Status, (" + GetStatusStr(this->dfu_status.bStatus) + ")");
        return -99;
    }
    if(this->dfu_state != DFUClass::DFUState::dfuMANIFEST)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuMANIFEST, after Download Zero "
                             "Length Command Get Status, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    if (!(this->manif_tolerant))
    {
        return 0;
    }

    /* wait for the PollTimeout */
#ifdef __linux__
    usleep(1000 * this->dfu_status.bwPollTimeOut);
#elif WIN32
    Sleep(this->dfu_status.bwPollTimeOut);
#endif
    /* check that the device is in the right state */
    DfuGetState();
    if (this->dfu_state == DFUClass::DFUState::stateUNKNOWN)
    {
        return -99;
    }

    if (this->dfu_state != DFUClass::DFUState::dfuMANIFEST_SYNC)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuMANIFEST_SYNC, after Download "
                             "Zero Length Command 1st Get Status, (" + GetStateStr(this->dfu_state)
                             + ")");
        return -99;
    }

    /* Send the Second Get Status */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if(this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Download Zero Length "
                             "Command 2nd Get Status, (" + GetStatusStr(this->dfu_status.bStatus) +
                             ")");
        return -99;
    }

    if (this->dfu_state != DFUClass::DFUState::dfuIDLE)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuIDLE, after Download Zero "
                             "Length Command 2nd Get Status, (" + GetStateStr(this->dfu_state) +
                             ")");
        return -99;
    }

    return 0;
}


/**
 * @brief DFUClass::DfuUploadPacket
 * The DFU_UPLOAD request is employed by the host to solicit firmware from the device
 * @param wBlockNum  the Packet number to be uploaded
 * @param data the buffer in which the data will be uploaded
 * @param length the buffer length  ( <= wTransferSize)
 * @return the number of transfered data on success, a negative integer otherwise
 */
int DFUClass::DfuUploadPacket(uint16_t wBlockNum, uint8_t *data, uint16_t length)
{
    /* check that the device is in the right state */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if ((this->dfu_state != dfuIDLE) && (this->dfu_state != dfuUPLOAD_IDLE))
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Device is not in the right state (" + GetStateStr(this->dfu_state)
                             + ") to send Upload command, Upload command will be sent anyway");
    }

    /* Send Buffer */
    int result = this->USBControlTransfer(
                 /* bmRequestType */     DFU_REQUEST_IN,
                 /* bRequest      */     DFU_UPLOAD,
                 /* wValue        */     wBlockNum,
                 /* wIndex        */     static_cast<uint16_t>(dfu_interface),
                 /* data          */     data,
                 /* length        */     length);

    if (result < 0)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to Send DFU Upload request, " + GetStrError(result));
        return result;
    }

    /* Send the Second Get Status */
    DfuGetStatus();
    if ((this->dfu_status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) ||
         (this->dfu_status.bState == DFUClass::DFUState::stateUNKNOWN))
    {
        return -99;
    }

    if (this->dfu_status.bStatus != DFUClass::DFUStatus::OK)
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATUS: OK, after Upload Command Get "
                             "Status, (" + GetStatusStr(this->dfu_status.bStatus) + ")");
        return -99;
    }

    if ((this->dfu_state != DFUClass::DFUState::dfuIDLE) &&
        (this->dfu_state != DFUClass::DFUState::dfuUPLOAD_IDLE))
    {
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU device did not switch to STATE: dfuIDLE/dfuUPLOAD_IDLE, after "
                             "Upload Command Get Status, (" + GetStateStr(this->dfu_state) + ")");
        return -99;
    }

    return result;
}


/**
 * @brief DFUClass::DfuDownload
 * Send a serie of DFUClass::DfuDownloadPacket requests according to the length of the data buffer
 * @param wBlockNum the initial Packet number to be downloaded
 * @param data the data buffer to be downloaded
 * @param length the data buffer length
 * @return 0 on success, negative integer otherwise
 */
int DFUClass::DfuDownload(uint16_t wBlockNum, const uint8_t *data, size_t length)
{
    size_t nbr = length / this->wTransferSize;
    uint16_t remain = length % this->wTransferSize;
    int result = 0x00;

    for (size_t i = 0; i < nbr; i++)
    {
        result = DfuDownloadPacket(wBlockNum++, (data + (i * this->wTransferSize)),
                                   this->wTransferSize);
        if (((result > 0) && (result != this->wTransferSize)) || result < 0)
            return -1;
    }

    if (remain)
    {
        result = DfuDownloadPacket(wBlockNum++, (data + (nbr * this->wTransferSize)), remain);
        if (((result > 0) && (static_cast<uint32_t>(result) != remain)) || result < 0)
            return -1;
    }

    return 0;
}


/**
 * @brief DFUClass::DfuUpload
 * Send a serie of DFUClass::DfuUploadPacket requests according to the length of the data buffer
 * @param wBlockNum the initial Packet number to be uploaded
 * @param data the buffer to store the uploaded data
 * @param length the data buffer length
 * @return 0 on success, negative integer otherwise
 */
int DFUClass::DfuUpload(uint16_t wBlockNum, uint8_t *data, size_t length)
{
    size_t nbr = length / this->wTransferSize;
    uint16_t remain = length % this->wTransferSize;
    int result = 0x0;

    for (size_t i = 0; i < nbr; i++)
    {
        result = DfuUploadPacket(wBlockNum++, (data + (i * this->wTransferSize)),
                                 this->wTransferSize);
        if (result < 0)
            return -1;
        if (result < this->wTransferSize)
            return 0;
    }

    if (remain)
    {
        result = DfuUploadPacket(wBlockNum, (data + (nbr * this->wTransferSize)), remain);
        if (result < 0)
            return -1;
        if (static_cast<uint32_t>(result) < remain)
            return 0;
    }

    return 0;
}

