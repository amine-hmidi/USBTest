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
#include <cstring>

/* C Includes */

/* User Includes */
#include "dfu_class.h"
#include <libusb-1.0/libusb.h>


/**
 * @brief DFUClass::DFUClass
 * @param vendor_id
 * @param product_id
 */
DFUClass::DFUClass(uint16_t vendor_id, uint16_t product_id)
    : StandardUSB(vendor_id, product_id)
{
    /* check device class */
    this->usb_class = StandardUSB::USBClassType::DFU_1_1;
}


/**
 * @brief DFUClass::~DFUClass
 */
DFUClass::~DFUClass()
{
    this->CloseDevice();
}


/* ********************************************************************************************** */
/* **************************** Device Handling/Discovering Functions *************************** */
/* ********************************************************************************************** */
/**
 * @brief DFUClass::OpenDevice
 * Open the device as a standard usb device, search for the dfu interface and the dfu functional
 * descriptor interface
 * @return 0 on success, -1 otherwise
 */
int8_t DFUClass::OpenDevice()
{
    int8_t result = this->StandardUSB::OpenDevice();
    if (result)
        return result;

    dfu_interface = GetDFUInterface();
    if (dfu_interface == 0xFFF)
    {
        this->StandardUSB::CloseDevice();
        return -1;
    }

    if (USBClaimInterface(dfu_interface))
    {
        this->StandardUSB::CloseDevice();
        return -1;
    }

    if (GetDFUFunctionalDescriptor() == nullptr)
    {
        this->StandardUSB::CloseDevice();
        return -1;
    }

    /* device can download */
    this->can_download = (this->dfu_func_desc.bmAttributes & 0x01);
    /* device can upload */
    this->can_upload = ((this->dfu_func_desc.bmAttributes & 0x02) >> 0x01);
    /* device manifestation tolerant */
    this->manif_tolerant = ((this->dfu_func_desc.bmAttributes & 0x04) >> 0x02);
    /* device will detach */
    this->will_detach = ((this->dfu_func_desc.bmAttributes & 0x08) >> 0x03);
    /* detach timeout */
    this->wDetachTimeOut = this->dfu_func_desc.wDetachTimeOut;
    /* control transfert size */
    this->wTransferSize = this->dfu_func_desc.wTransferSize;

    return 0;
}


/**
 * @brief DFUClass::CloseDevice
 * @return 0 allways
 */
int8_t DFUClass::CloseDevice()
{
    this->dfu_status.Clear();
    dfu_state = stateUNKNOWN;

    this->can_download = 0x00;
    this->can_upload = 0x00;
    this->manif_tolerant = 0x00;
    this->will_detach = 0x00;
    this->wDetachTimeOut = 0x00;
    this->wTransferSize = 0x00;
    this->dfu_interface = 0xFFF;

    if (dfu_interface != 0xFFF)
        USBReleaseInterface(dfu_interface);

    this->dfu_func_desc.Clear();

    this->StandardUSB::CloseDevice();

    return 0;
}


/**
 * @brief DFUClass::ReOpenDevice
 * @return 0 on success, -1 otherwise
 */
int8_t DFUClass::ReOpenDevice()
{
    this->CloseDevice();
    return this->OpenDevice();
}


/* ********************************************************************************************** */
/* ************************************ Descriptors Requests ************************************ */
/* ********************************************************************************************** */
/**
 * @brief DFUClass::GetDFUInterface
 * Search for the dfu class interface, according to bInterfaceClass, bInterfaceSubClass and
 * bInterfaceProtocol fields.
 * @return the interface index on success, 0xFFF otherwise
 */
int DFUClass::GetDFUInterface()
{
    for(int i = 0; i < usb_config_descriptor->bNumInterfaces; i++)
    {
        const struct libusb_interface &interface = usb_config_descriptor->interface[i];
        const struct libusb_interface_descriptor &descriptor = interface.altsetting[0];
        if ((descriptor.bInterfaceClass == 0xFE) && (descriptor.bInterfaceSubClass == 0x01) &&
            (descriptor.bInterfaceProtocol == 0x02))
        {
            return i;
        }
    }

    usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Device is not DFU capable");
    return 0xFFF;
}


/**
 * @brief DFUClass::GetDFUFunctionalDescriptor
 * Search for the DFU functional descriptor in the interface extra bytes, according to the bLength
 * and bDescriptorType fields.
 * @return a const pointer to a DFUFunctional descriptor on success, nullptr otherwise
 */
const DFUClass::DFUFunctionalDescriptor *DFUClass::GetDFUFunctionalDescriptor()
{
    if (dfu_interface == 0xFFF)
        return nullptr;

    const struct libusb_interface &interface = usb_config_descriptor->interface[dfu_interface];
    for (int j = 0; j < interface.num_altsetting; j++)
    {
        const struct libusb_interface_descriptor &descriptor = interface.altsetting[j];
        if (!descriptor.extra_length)
            continue;
        if ((descriptor.extra[0] != 0x09) && (descriptor.extra[1] != 0x21))
            continue;

        this->dfu_func_desc.bLength = descriptor.extra[0];
        this->dfu_func_desc.bDescriptorType = descriptor.extra[1];
        this->dfu_func_desc.bmAttributes = descriptor.extra[2];
        this->dfu_func_desc.wDetachTimeOut = static_cast<uint16_t>(descriptor.extra[3] |
                                             (static_cast<uint32_t>(descriptor.extra[4]) << 8));
        this->dfu_func_desc.wTransferSize = static_cast<uint16_t>(descriptor.extra[5] |
                                            (static_cast<uint32_t>(descriptor.extra[6]) << 8));
        this->dfu_func_desc.bcdDFUVersion = static_cast<uint16_t>(descriptor.extra[7] |
                                            (static_cast<uint32_t>(descriptor.extra[8]) << 8));

        return &dfu_func_desc;
    }

    usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                         "Device is missing DFU functional descriptor");
    return nullptr;
}


/* ********************************************************************************************** */
/* ************************************* Messaging Functions ************************************ */
/* ********************************************************************************************** */
/**
 * @brief DFUClass::DisplayDescriptorsSet
 */
void DFUClass::DisplayDescriptorsSet()
{
    if (this->usb_device_descriptor)
        DisplayDeviceDescriptor();

    if (this->usb_config_descriptor)
        DisplayConfigurationDescriptor();

    if(this->dfu_func_desc.bLength)
        DisplayDFUFunctionalDescriptor();
}


/**
 * @brief DFUClass::DisplayDFUFunctionalDescriptor
 */
void DFUClass::DisplayDFUFunctionalDescriptor()
{
    std::stringstream stream;
    stream << std::hex << std::setfill ('0');

    stream << "\tDFU Functional Descriptor:";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\tbLength            : 0x" << std::setw(2)
              << static_cast<uint32_t>(dfu_func_desc.bLength);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\tbDescriptorType    : 0x" << std::setw(2)
              << static_cast<uint32_t>(dfu_func_desc.bDescriptorType);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\tbmAttributes       : 0x" << std::setw(2)
              << static_cast<uint32_t>(dfu_func_desc.bmAttributes);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\twDetachTimeOut     : 0x" << std::setw(4)
              << static_cast<uint32_t>(dfu_func_desc.wDetachTimeOut);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\twTransferSize      : 0x" << std::setw(4)
              << static_cast<uint32_t>(dfu_func_desc.wTransferSize);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());
    stream << "\t\tbcdDFUVersion      : 0x" << std::setw(4)
              << static_cast<uint32_t>(dfu_func_desc.bcdDFUVersion);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief DFUClass::GetStatusStr
 * Converts a DFUClass::DFUStatus into it's std::string meaning
 * @param status a DFUClass::DFUStatus
 * @return a std::string describing the dfu status
 */
std::string DFUClass::GetStatusStr(DFUClass::DFUStatus status)
{
    std::string str;
    switch(status)
    {
    case OK:
        str = "OK";
        break;

        /* File is not targeted for use by this device */
    case errTARGET:
        str = "errTARGET";
        break;

        /* File is for this device but fails some vendor-specific
     * verification test. */
    case errFILE:
        str = "errFILE";
        break;

        /* Device is unable to write memory */
    case errWRITE:
        str = "errWRITE";
        break;

        /* Memory erase function failed. */
    case errERASE:
        str = "errERASE";
        break;

        /* Memory erase check failed */
    case errCHECK_ERASED:
        str = "errCHECK_ERASED";
        break;

        /* Program memory function failed */
    case errPROG:
        str = "errPROG";
        break;

        /* Programmed memory failed verification */
    case errVERIFY:
        str = "errVERIFY";
        break;

        /* Cannot program memory due to received address that is
     * out of range */
    case errADDRESS:
        str = "errADDRESS";
        break;

        /* Received DFU_DNLOAD with wLength = 0, but device does
     * not think it has all of the data yet */
    case errNOTDONE:
        str = "errNOTDONE";
        break;

        /* Device’s firmware is corrupt. It cannot return to run-time
     * (non-DFU) operations */
    case errFIRMWARE:
        str = "errFIRMWARE";
        break;

        /* iString indicates a vendor-specific error */
    case errVENDOR:
        str = "errVENDOR";
        break;

        /* Device detected unexpected USB reset signaling */
    case errUSBR:
        str = "errUSBR";
        break;

        /* Device detected unexpected power on reset */
    case errPOR:
        str = "errPOR";
        break;

        /* Something went wrong, but the device does not know what it
     * was */
    case errUNKNOWN:
        str = "errUNKNOWN";
        break;

        /* Device stalled an unexpected request */
    case errSTALLEDPKT:
        str = "errSTALLEDPKT";
        break;

        /* Unkown */
    case statusUNKNOWN:
        str = "statusUNKNOWN";
        break;

    }

    return str;
}


/**
 * @brief DFUClass::GetStateStr
 * Converts a DFUClass::DFUState into it's std::string meaning
 * @param state a DFUClass::DFUState
 * @return a std::string describing the dfu state
 */
std::string DFUClass::GetStateStr(DFUClass::DFUState state)
{
    std::string str;
    switch(state)
    {
    /* Device is running its normal application */
    case appIDLE:
        str = "appIDLE";
        break;

    /* Device is running its normal application, has received the
     * DFU_DETACH request, and is waiting for a USB reset */
    case appDETACH:
        str = "appDETACH";
        break;

    /* Device is operating in the DFU mode and is waiting for
     * requests */
    case dfuIDLE:
        str = "dfuIDLE";
        break;

    /* Device has received a block and is waiting for the host to
     * solicit the status via DFU_GETSTATUS */
    case dfuDNLOAD_SYNC:
        str = "dfuDNLOAD_SYNC";
        break;

    /* Device is programming a control-write block into its
     * nonvolatile memories */
    case dfuDNBUSY:
        str = "dfuDNBUSY";
        break;

    /* Device is processing a download operation. Expecting
     * DFU_DNLOAD requests */
    case dfuDNLOAD_IDLE:
        str = "dfuDNLOAD_IDLE";
        break;

    /* Device has received the final block of firmware from the host
     * and is waiting for receipt of DFU_GETSTATUS to begin the
     * Manifestation phase; or device has completed the
     * Manifestation phase and is waiting for receipt of
     * DFU_GETSTATUS. (Devices that can enter this state after
     * the Manifestation phase set bmAttributes bit
     * bitManifestationTolerant to 1.) */
    case dfuMANIFEST_SYNC:
        str = "dfuMANIFEST_SYNC";
        break;

    /* Device is in the Manifestation phase. (Not all devices will be
     * able to respond to DFU_GETSTATUS when in this state.) */
    case dfuMANIFEST:
        str = "dfuMANIFEST";
        break;

    /* Device has programmed its memories and is waiting for a
     * USB reset or a power on reset. (Devices that must enter
     * this state clear bitManifestationTolerant to 0.) */
    case dfuMANIFEST_WAIT_RESET:
        str = "dfuMANIFEST_WAIT_RESET";
        break;

    /* The device is processing an upload operation. Expecting
     * DFU_UPLOAD requests. */
    case dfuUPLOAD_IDLE:
        str = "dfuUPLOAD_IDLE";
        break;

    /* An error has occurred. Awaiting the DFU_CLRSTATUS
     * request */
    case dfuERROR:
        str = "dfuERROR";
        break;

    /* Unknown State */
    case stateUNKNOWN:
        str = "stateUNKNOWN";
        break;
    }

    return str;
}


/**
 * @brief DFUClass::DisplayDfuStatus
 */
void DFUClass::DisplayDfuStatus()
{
    std::stringstream stream;
    std::cout << std::hex << std::setfill('0');

    stream << "DFU 1.1 Status:";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());

    stream << "\tbStatus       : 0x" << std::setw(2)
              << static_cast<uint32_t>(this->dfu_status.bStatus) << " ("
              << GetStatusStr(this->dfu_status.bStatus) << ")";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());

    stream << "\tbwPollTimeout : 0x" << std::setw(4)
              << static_cast<uint32_t>(this->dfu_status.bwPollTimeOut);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());

    stream << "\tbState        : 0x" << std::setw(2)
              << static_cast<uint32_t>(this->dfu_status.bState)
              << " (" << GetStateStr(this->dfu_status.bState) << ")";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());

    stream << "\tiString       : 0x" << std::setw(2)
              << static_cast<uint32_t>(this->dfu_status.iString);
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief DFUClass::DisplayDfuState
 */
void DFUClass::DisplayDfuState()
{
    std::stringstream stream;
    stream << std::hex << std::setfill('0');

    stream << "DFU 1.1 State:";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
    stream.str(std::string());

    stream << "\tbState       : 0x" << std::setw(2) << static_cast<uint32_t>(this->dfu_state)
              << " (" << GetStateStr(this->dfu_state) << ")";
    usb_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


