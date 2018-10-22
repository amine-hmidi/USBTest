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

#if defined (STANDARD_USB)

/* C++ Includes */
#include <iostream>
#include <iomanip>
#include <sstream>

/* C Includes */

/* User Includes */
#include "standard_usb.h"
#include <libusb-1.0/libusb.h>


/* ********************************************************************************************** */
/* ************************************ Descriptors Requests ************************************ */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::GetDeviceDescriptor
 * Request the usb device descriptor
 * @return a pointer to libusb_device_descriptor
 */
libusb_device_descriptor *StandardUSB::GetDeviceDescriptor()
{
    libusb_device_descriptor *l_dev_desc = new(std::nothrow)libusb_device_descriptor();
    if (!l_dev_desc)
    {
        std::stringstream stream;
        stream << "Unable to request USB device descriptor, Memory allocation error";
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, stream.str());
        return nullptr;
    }

    int result = DeviceGetDescriptor(LIBUSB_DT_DEVICE, 0x01,  0x0409, \
                                     static_cast<uint8_t *>(static_cast<void *>(l_dev_desc)),\
                                     sizeof(libusb_device_descriptor));
    if (result <= 0)
    {
        std::stringstream stream;
        stream << "Unable to request USB device descriptor, " << GetStrError(result);
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, stream.str());
        delete l_dev_desc;
        return nullptr;
    }

    return l_dev_desc;
}


/**
 * @brief StandardUSB::GetConfigurationDescriptor
 * Request the configuration descriptor
 * @param index configuration index
 * @return a pointer a libusb_config_decriptor
 */
libusb_config_descriptor *StandardUSB::GetConfigurationDescriptor(uint8_t index)
{
    libusb_config_descriptor *l_conf = nullptr;
    int result = libusb_get_config_descriptor(usb_device, index, &l_conf);
    if (result < 0)
    {
        std::stringstream stream;
        stream << "Unable to request USB Configuration descriptor, " << GetStrError(result);
        usb_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, stream.str());
        return nullptr;
    }

    return l_conf;
}


/**
 * @brief StandardUSB::GetStringDescriptor
 * Request a string descriptor
 * @param index string descriptor index
 * @param language string descriptor language
 * @return the string descriptor
 */
std::string StandardUSB::GetStringDescriptor(uint8_t index, uint16_t language)
{
    std::string str;
    uint8_t data[255] = {0x00};

    int result = DeviceGetDescriptor(0x3, index, language, data, 255);
    if (result < 0)
        return str;

    for (int i = 2; i < result; i++)
    {
        if (*(data + i) != 0)
            str += *(reinterpret_cast<int8_t *>(reinterpret_cast<void *>(data)) + i);
    }

    return str;
}


#endif //STANDARD_USB
