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

/* C Includes */

/* User Includes */
#include "standard_usb.h"


unsigned int StandardUSB::time_out = 3000;


/* ********************************************************************************************** */
/* ******************************** Class Constructor/Destructor ******************************** */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::StandardUSB
 * Takes the idVendor and idProduct as parameters in order
 * to identify the usb device to which we will be connected
 * and then proceeds by initializing libusb context (default).
 * @param vendor_id usb device idVendor
 * @param product_id usb device idProduct
 */
StandardUSB::StandardUSB(uint16_t vendor_id, uint16_t product_id)
{
    this->vendor_id = vendor_id;
    this->product_id = product_id;

    /* Init context */
    libusb_init(&context);

    /* check device class */
    this->usb_class = USBClassType::NONE;
}


/**
 * @brief StandardUSB::~StandardUSB
 * Destroys the libusb Default context
 */
StandardUSB::~StandardUSB()
{
    /*  Close device if it still open */
    this->CloseDevice();

    /* Exit context */
    libusb_exit(context);
}


/* ********************************************************************************************** */
/* ************************************* Messaging Functions ************************************ */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::GetStrError
 * Converts a libusb error into it's std::string meaning
 * @param error libusb_error
 * @return libusb_error as a std::string
 */
std::string StandardUSB::GetStrError(libusb_error error)
{
    std::string error_msg;

    switch (error)
    {
        case LIBUSB_SUCCESS:
            error_msg = "no error";
            break;

        case LIBUSB_ERROR_IO:
            error_msg = "Input/output error";
            break;

        case LIBUSB_ERROR_INVALID_PARAM:
            error_msg = "Invalid parameter";
            break;

        case LIBUSB_ERROR_ACCESS:
            error_msg = "Access denied (insufficient permissions)";
            break;

        case LIBUSB_ERROR_NO_DEVICE:
            error_msg = "No such device (it may have been disconnected)";
            break;

        case LIBUSB_ERROR_NOT_FOUND:
            error_msg = "Entity not found";
            break;

        case LIBUSB_ERROR_BUSY:
            error_msg = "Resource busy";
            break;

        case LIBUSB_ERROR_TIMEOUT:
            error_msg = "Operation timed out";
            break;

        case LIBUSB_ERROR_OVERFLOW:
            error_msg = "Overflow";
            break;

        case LIBUSB_ERROR_PIPE:
            error_msg = "Pipe error";
            break;

        case LIBUSB_ERROR_INTERRUPTED:
            error_msg = "System call interrupted (perhaps due to signal)";
            break;

        case LIBUSB_ERROR_NO_MEM:
            error_msg = "Insufficient memory";
            break;

        case LIBUSB_ERROR_NOT_SUPPORTED:
            error_msg = "Operation not supported or unimplemented on this platform";
            break;

        case LIBUSB_ERROR_OTHER:
        default:
            error_msg = "Other error";
            break;
    }

    return error_msg;
}


/**
 * @brief StandardUSB::DisplayDescriptorsSet
 * Displays USB Device Descriptor and USB Configuration Descriptor
 * (other standard descriptors will be added here)
 */
void StandardUSB::DisplayDescriptorsSet()
{
    if (this->usb_device_descriptor)
        DisplayDeviceDescriptor();

    if (this->usb_config_descriptor)
        DisplayConfigurationDescriptor(true);
}


/**
 * @brief StandardUSB::DisplayDeviceDescriptor
 * Displays the USB Device Descriptor
 */
void StandardUSB::DisplayDeviceDescriptor()
{
    std::cout << std::hex << std::setfill ('0');
    std::cout << "Device Descriptor:\n";
    std::cout << "\tbLength            : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bLength)          << "\n";
    std::cout << "\tbDescriptorType    : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bDescriptorType)  << "\n";
    std::cout << "\tbcdUSB             : 0x" << std::setw(4) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bcdUSB)           << "\n";
    std::cout << "\tbDeviceClass       : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bDeviceClass)     << "\n";
    std::cout << "\tbDeviceSubClass    : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bDeviceSubClass)  << "\n";
    std::cout << "\tbDeviceProtocol    : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bDeviceProtocol)  << "\n";
    std::cout << "\tbMaxPacketSize     : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bMaxPacketSize0)  << "\n";
    std::cout << "\tidVendor           : 0x" << std::setw(4) <<\
                 static_cast<uint32_t>(usb_device_descriptor->idVendor)         << "\n";
    std::cout << "\tidProduct          : 0x" << std::setw(4) <<\
                 static_cast<uint32_t>(usb_device_descriptor->idProduct)        << "\n";
    std::cout << "\tbcdDevice          : 0x" << std::setw(4) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bcdDevice)        << "\n";
    std::cout << "\tiManufacturer      : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->iManufacturer) << " (" << \
                 GetStringDescriptor(usb_device_descriptor->iManufacturer, 0x0409) << ")\n";
    std::cout << "\tiProduct           : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->iProduct) << " (" <<
                 GetStringDescriptor(usb_device_descriptor->iProduct, 0x0409) << ")\n";
    std::cout << "\tiSerialNumber      : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->iSerialNumber) << " (" << \
                 GetStringDescriptor(usb_device_descriptor->iSerialNumber, 0x0409) << ")\n";
    std::cout << "\tbNumConfigurations : 0x" << std::setw(2) <<\
                 static_cast<uint32_t>(usb_device_descriptor->bNumConfigurations) << "\n";
}


/**
 * @brief StandardUSB::DisplayConfigurationDescriptor
 * Displays the USB Configuration Descriptor, if the display_extra
 * flag is set to true, then it will also display extra bytes found
 * in libusb_config_descriptor, libusb_interface_descriptor and
 * libusb_endpoint_descriptor.
 * @param display_extra flag to display extra data found in each descriptor
 */
void StandardUSB::DisplayConfigurationDescriptor(bool display_extra)
{
    std::cout << std::hex << std::setfill ('0');
    std::cout << "Configuration Descriptor:\n";
    std::cout << "\tbLength             : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->bLength)             << "\n";
    std::cout << "\tbDescriptorType     : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->bDescriptorType)     << "\n";
    std::cout << "\twTotalLength        : 0x" << std::setw(4) << \
                 static_cast<uint32_t>(usb_config_descriptor->wTotalLength)        << "\n";
    std::cout << "\tbNumInterfaces      : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->bNumInterfaces)      << "\n";
    std::cout << "\tbConfigurationValue : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->bConfigurationValue) << "\n";
    std::cout << "\tiConfiguration      : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->iConfiguration) << " (" << \
                 GetStringDescriptor(usb_config_descriptor->iConfiguration, 0x0409) << ")\n";
    std::cout << "\tbmAttributes        : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->bmAttributes)        << "\n";
    std::cout << "\tbMaxPower           : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(usb_config_descriptor->MaxPower)            << "\n";

    for (uint8_t i = 0; i < usb_config_descriptor->bNumInterfaces; i++)
        DisplayInterfaceDescriptor(usb_config_descriptor->interface[i], display_extra);

    if(display_extra && usb_config_descriptor->extra_length)
    {
        std::cout << "Configuration Descriptor Extra Bytes:\n";
        for (int i = 0; i < usb_config_descriptor->extra_length; i++)
            std::cout << "\tByte nbr 0x" << std::setw(2) << static_cast<uint32_t>(i) << "   :0x" <<\
                         std::setw(2) << static_cast<uint32_t>(*(usb_config_descriptor->extra + i))\
                      << "\n";
    }
}


/**
 * @brief StandardUSB::DisplayInterfaceDescriptor
 * Iterates throw the interface alternate setting and displays each
 * one of them, if the display_extra flag is set to true, then it
 * will also display extra bytes found in libusb_interface_descriptor
 * and libusb_endpoint_descriptor.
 * @param interface reference to libusb_interface
 * @param display_extra flag to display extra data found in each descriptor
 */
void StandardUSB::DisplayInterfaceDescriptor(const struct libusb_interface &interface, \
                                             bool display_extra)
{
    std::cout << std::hex << std::setfill ('0');
    std::cout << "\tInterface Descriptor:\n";
    for (int i = 0; i < interface.num_altsetting; i++)
        DisplayInterfaceAltDescriptor(interface.altsetting[i], display_extra);
}


/**
 * @brief StandardUSB::DisplayInterfaceAltDescriptor
 * Displays teh USB Interface Alternate Setting Descriptor, if the
 * the display_extra flag is set to true, then it will also display
 * extra bytes found in libusb_interface_descriptor and
 * libusb_endpoint_descriptor.
 * @param altset reference to libusb_interface_descriptor
 * @param display_extra flag to display extra data found in each descriptor
 */
void StandardUSB::DisplayInterfaceAltDescriptor(const struct libusb_interface_descriptor &altset, \
                                                bool display_extra)
{
    std::cout << std::hex << std::setfill ('0');
    std::cout << "\t\tAlternate Setting Descriptor:\n";
    std::cout << "\t\t\tbLength            : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bLength)             << "\n";
    std::cout << "\t\t\tbDescriptorType    : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bDescriptorType)     << "\n";
    std::cout << "\t\t\tbInterfaceNumber   : 0x" << std::setw(4) << \
                 static_cast<uint32_t>(altset.bInterfaceNumber)    << "\n";
    std::cout << "\t\t\tbAlternateSetting  : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bAlternateSetting)   << "\n";
    std::cout << "\t\t\tbNumEndpoints      : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bNumEndpoints)       << "\n";
    std::cout << "\t\t\tbInterfaceClass    : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bInterfaceClass)     << "\n";
    std::cout << "\t\t\tbInterfaceSubClass : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bInterfaceSubClass)  << "\n";
    std::cout << "\t\t\tbInterfaceProtocol : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.bInterfaceProtocol)  << "\n";
    std::cout << "\t\t\tiInterface         : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(altset.iInterface) << " (" << \
                 GetStringDescriptor(altset.iInterface, 0x0409) << ")\n";

    for (int i = 0; i < altset.bNumEndpoints; i++)
        DisplayEndpointDescriptor(altset.endpoint[i], display_extra);

    if(display_extra && altset.extra_length)
    {
        std::cout << "\t\tAlternate Setting Descriptor Extra Bytes:\n";
        for (int i = 0; i < altset.extra_length; i++)
            std::cout << "\t\t\tByte nbr 0x" << std::setw(2) << static_cast<uint32_t>(i) << \
                         "      :0x" << std::setw(2) << static_cast<uint32_t>(*(altset.extra + i)) \
                      << "\n";
    }
}


/**
 * @brief StandardUSB::DisplayEndpointDescriptor
 * Displays teh USB Interface EndPoint Descriptor, if the
 * the display_extra flag is set to true, then it will also display
 * extra bytes found in libusb_endpoint_descriptor.
 * @param endpoint reference to libusb_endpoint_descriptor
 * @param display_extra flag to display extra data found in each descriptor
 */
void StandardUSB::DisplayEndpointDescriptor(const struct libusb_endpoint_descriptor &endpoint, \
                                            bool display_extra)
{
    std::cout << std::hex << std::setfill ('0');
    std::cout << "\t\t\tEndpoint Descriptor:\n";
    std::cout << "\t\t\t\tbLength            : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(endpoint.bLength)             << "\n";
    std::cout << "\t\t\t\tbDescriptorType    : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(endpoint.bDescriptorType)     << "\n";
    std::cout << "\t\t\t\tbEndpointAddress   : 0x" << std::setw(4) << \
                 static_cast<uint32_t>(endpoint.bEndpointAddress)    << "\n";
    std::cout << "\t\t\t\tbmAttributes       : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(endpoint.bmAttributes)        << "\n";
    std::cout << "\t\t\t\tbInterval          : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(endpoint.wMaxPacketSize)      << "\n";
    std::cout << "\t\t\t\tbInterfaceClass    : 0x" << std::setw(2) << \
                 static_cast<uint32_t>(endpoint.bInterval)           << "\n";

    if(display_extra && endpoint.extra_length)
    {
        std::cout << "\t\t\tEndpoint Descriptor Extra Bytes:\n";
        for (int i = 0; i < endpoint.extra_length; i++)
        {
            std::cout << "\t\t\t\t\tByte nbr 0x" << std::setw(2) << static_cast<uint32_t>(i) << \
                         "   :0x"<< std::setw(2) << static_cast<uint32_t>(*(endpoint.extra + i)) <<\
                         "\n";
        }
    }
}


/**
 * @brief StandardUSB::DisplayData8
 * Displays data as 8bits in hex
 * @param data data to be displayed
 * @param size size of data
 */
void StandardUSB::DisplayData8(uint8_t *data, size_t size)
{
    std::cout << "\n";
    std::cout << std::hex << std::setfill ('0');
    std::cout << "OFFSET           0x00   0x01   0x02   0x03   0x04   0x05   0x06   0x07   0x08   "\
                 "0x09   0x0A   0x0B   0x0C   0x0D   0x0E   0x0F\n\n";

    size_t nbr = size / 0x10;
    uint32_t remain = size % 0x10;

    for (size_t i = 0; i < nbr; i++)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x10) << "       ";
        for (uint32_t j = 0; j < 0x10; j++)
        {
            std::cout << "0x" << std::setw(2) << static_cast<uint32_t>(*(data + (i * 0x10) + j));
            if (j != 0x0F)
                std::cout << "   ";
        }
        std::cout << "\n";
    }

    if (remain)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(0x10 * nbr) << "       ";
        for (uint32_t j = 0; j < remain; j++)
        {
            std::cout << "0x" << std::setw(2) << static_cast<uint32_t>(*(data + (nbr * 0x10) + j));
            if (j != 0x0F)
                std::cout << "   ";
        }
        std::cout << "\n";
    }
}


/**
 * @brief StandardUSB::DisplayData16
 * Displays data as 16bits in hex
 * @param data data to be displayed
 * @param size size of data
 */
void StandardUSB::DisplayData16(uint8_t *data, size_t size)
{
    std::cout << "\n";
    std::cout << std::hex << std::setfill ('0');
    std::cout << "OFFSET           0x0000   0x0002   0x0004   0x0006   0x0008   0x000A   0x000C   "\
                 "0x000E\n\n";

    size_t nbr = size / 0x10;
    uint32_t remain = size % 0x10;

    for (size_t i = 0; i < nbr; i++)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x10) << "       ";
        for (uint32_t j = 0; j < 0x10; j += 2)
        {
            uint16_t value = static_cast<uint16_t>((*(data + (i * 0x10) + j)) | \
                             (static_cast<uint32_t>((*(data + (i * 0x10) + j + 1))) << 8));
            std::cout << "0x" << std::setw(4) << static_cast<uint32_t>(value);
            if (j != 0x0E)
                std::cout << "   ";
        }
        std::cout << "\n";
    }

    if (remain)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(0x10 * nbr) << "       ";
        for (uint32_t j = 0; j < remain; j += 2)
        {
            uint16_t value = static_cast<uint16_t>((*(data + (nbr * 0x10) + j)) | \
                             (static_cast<uint32_t>((*(data + (nbr * 0x10) + j + 1))) << 8));
            std::cout << "0x" << std::setw(4) << static_cast<uint32_t>(value);
            if (j != 0x0E)
                std::cout << "   ";
        }
        std::cout << "\n";
    }
}


/**
 * @brief StandardUSB::DisplayData32
 * Displays data as 32bits in hex
 * @param data data to be displayed
 * @param size size of data
 */
void StandardUSB::DisplayData32(uint8_t *data, size_t size)
{
    std::cout << "\n";
    std::cout << std::hex << std::setfill ('0');
    std::cout << "OFFSET           0x00000000   0x00000004   0x00000008   0x0000000C   0x00000010"\
                 "   0x00000014   0x00000018   0x0000001C\n\n";

    size_t nbr = size / 0x20;
    uint32_t remain = size % 0x20;

    for (size_t i = 0; i < nbr; i++)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x20) << "       ";
        for (uint32_t j = 0; j < 0x20; j += 4)
        {
            uint32_t value = (*(data + (i * 0x20) + j)) | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 3)))) << 24);
            std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(value);
            if (j != 0x1C)
                std::cout << "   ";
        }
        std::cout << "\n";
    }

    if (remain)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(0x20 * nbr) << "       ";
        for (uint32_t j = 0; j < remain; j += 4)
        {
            uint32_t value = (*(data + (nbr * 0x20) + j)) | \
                             ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 3)))) << 24);
            std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(value);
            if (j != 0x1C)
                std::cout << "   ";
        }
        std::cout << "\n";
    }
}


/**
 * @brief StandardUSB::DisplayData64
 * Displays data as 64bits in hex
 * @param data data to be displayed
 * @param size size of data
 */
void StandardUSB::DisplayData64(uint8_t *data, size_t size)
{
    std::cout << "\n";
    std::cout << std::hex << std::setfill ('0');
    std::cout << "OFFSET           0x0000000000000000        0x0000000000000008        "\
                 "0x0000000000000010        0x0000000000000018\n\n";

    size_t nbr = size / 0x20;
    uint32_t remain = size % 0x20;

    for (size_t i = 0; i < nbr; i++)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x20) << "       ";
        for (uint32_t j = 0; j < 0x20; j += 8)
        {
            uint64_t value = (*(data + (i * 0x20) + j)) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 3)))) << 24) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 4)))) << 32) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 5)))) << 40) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 6)))) << 48) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 7)))) << 56);
            std::cout << "0x" << std::setw(16) << static_cast<uint64_t>(value);
            if (j != 0x1C)
                std::cout << "        ";
        }
        std::cout << "\n";
    }

    if (remain)
    {
        std::cout << "0x" << std::setw(8) << static_cast<uint32_t>(0x20 * nbr) << "       ";
        for (uint32_t j = 0; j < remain; j += 8)
        {
            uint64_t value = (*(data + (nbr * 0x20) + j)) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 3)))) << 24) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 4)))) << 32) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 5)))) << 40) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 6)))) << 48) | \
                             ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 7)))) << 56);

            std::cout << "0x" << std::setw(16) << static_cast<uint64_t>(value);
            if (j != 0x1C)
                std::cout << "        ";
        }
        std::cout << "\n";
    }
}


/* ********************************************************************************************** */
/* **************************** Device Handling/Discovering Functions *************************** */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::ListUSBDevices
 * Display the list of USB devices connected to the host
 */
void StandardUSB::ListUSBDevices()
{
    std::cout << "\n";
    std::cout << "Info: USB devices' list:\n";

    /* init default context */
    libusb_init(nullptr);

    /* discover devices */
    libusb_device **list;
    ssize_t count = libusb_get_device_list(nullptr, &list);
    if (count < 0)
    {
        std::cout << "Error:  Unable to list USB devices currently attached to the system, " << \
                     GetStrError(static_cast<libusb_error>(count)) << "\n";
        return ;
    }

    std::cout << std::hex << std::setfill ('0');
    for (ssize_t i = 0; i < count; i++)
    {
        /* Check vendor ID & Product ID */
        libusb_device_descriptor dev_desc;
        if (libusb_get_device_descriptor(list[i], &dev_desc))
            continue;

        std::cout << "Info:\tidVendor: 0x" << std::setw(4) << dev_desc.idVendor << " idProduct: 0x"\
                  << std::setw(4) << dev_desc.idProduct ;

        /* open device */
        libusb_device_handle *handle = nullptr;
        if (libusb_open(list[i], &handle))
            continue;

        /* get the device string descriptor */
        uint8_t data[512] = {0x00};
        uint8_t bmRequestType = (LIBUSB_ENDPOINT_IN | LIBUSB_REQUEST_TYPE_STANDARD | \
                                 LIBUSB_RECIPIENT_DEVICE);
        uint16_t wValue = static_cast<uint16_t>((static_cast<uint32_t>(LIBUSB_DT_STRING) << 8) | \
                                                dev_desc.iProduct);

        int result = libusb_control_transfer(handle,\
                                             /* bmRequestType */     bmRequestType,
                                             /* bRequest      */     LIBUSB_REQUEST_GET_DESCRIPTOR,
                                             /* wValue        */     wValue,
                                             /* wIndex        */     0x0409,
                                             /* data          */     data,
                                             /* length        */     512,
                                             /* timeout       */     StandardUSB::time_out);

        /* close the device */
        libusb_close(handle);

        if (result <= 0)
        {
            std::cout << "\n";
            continue;
        }

        std::string product;
        for (int j = 2; j < result; j++)
        {
            if (data[j] != 0x00)
                product += static_cast<int8_t>(data[j]);
        }

        std::cout << " " << product << "\n";
    }

    /* free devices' list */
    libusb_free_device_list(list, 1);

    /* destroy context */
    libusb_exit(nullptr);
}


/**
 * @brief StandardUSB::OpenDevice
 * Opens a USB device based on its idVendor and idProduct.
 * This function starts by searching for the device with
 * its idv/idp. Once found, it opens it and trys its best
 * to request all the standard usb descriptors. If any of
 * these steps fails than the device willl be automaticlly
 * closed.
 * @return 0 on success, -1 otherwise
 */
int8_t StandardUSB::OpenDevice()
{
    /* get usb device */
    this->usb_device = GetUSBDevice();
    if (!this->usb_device)
        return -1;

    /* get usb handle */
    this->usb_handle = GetUSBHandle(this->usb_device);
    if (!this->usb_handle)
    {
        libusb_unref_device(this->usb_device);
        return -1;
    }

    /* get device descriptor */
    this->usb_device_descriptor = GetDeviceDescriptor();
    if (!this->usb_device_descriptor)
    {
        CloseDevice();
        return -1;
    }

    /* get the current configuration descriptor */
    int config = 0x00;
    if (!libusb_get_configuration(this->usb_handle, &config) && config)
    {
        /* requets the active configuration descriptor */
        this->usb_config_descriptor = GetConfigurationDescriptor(static_cast<uint8_t>(config - 1));
        if (!this->usb_config_descriptor)
        {
            CloseDevice();
            return -1;
        }

        return 0;
    }

    /* otherwise set the device configuration to 0x01 */
    int result = libusb_set_configuration(this->usb_handle, 0x01);
    if (result)
    {
        std::cout << "Error: Unable to set the device configuration to 0x01, " << \
                     GetStrError(static_cast<libusb_error>(result)) << "\n";
        CloseDevice();
        return -1;
    }

    /* requets the active configuration descriptor */
    this->usb_config_descriptor = GetConfigurationDescriptor(0x00);
    if (!this->usb_config_descriptor)
    {
        CloseDevice();
        return -1;
    }

    return 0;
}


/**
 * @brief StandardUSB::CloseDevice
 * Release all the usb device's resources and close it
 * @return allways 0
 */
int8_t StandardUSB::CloseDevice()
{
    /*  */
    if (this->usb_config_descriptor)
    {
        libusb_free_config_descriptor(this->usb_config_descriptor);
        this->usb_config_descriptor = nullptr;
    }

    /*  */
    if (this->usb_device_descriptor)
    {
        delete this->usb_device_descriptor;
        this->usb_device_descriptor = nullptr;
    }

    /*  */
    if (this->usb_handle)
    {
        libusb_close(this->usb_handle);
        this->usb_handle = nullptr;
    }

    /*  */
    if (this->usb_device)
    {
        libusb_unref_device(this->usb_device);
        this->usb_device = nullptr;
    }

    return 0;
}


/**
 * @brief StandardUSB::ReOpenDevice
 * Closes the devices and release all of its resources
 * and try to re-opened. Keep in mind that if the device
 * changes its idProduct after a usb reset or a usb device
 * reconfiguration this function will mostly fail.
 * @return 0 on success, -1 otherwise
 */
int8_t StandardUSB::ReOpenDevice()
{
    CloseDevice();

    return OpenDevice();
}


/**
 * @brief StandardUSB::GetUSBDevice
 * Searchs for the USB device with the given idVendor and
 * idProduct. If many devices with the same pair of idVendor
 * idProduct are connected, it will return the first one
 * encountered
 * @return libusb_device * on success, nullptr otherwise
 */
libusb_device *StandardUSB::GetUSBDevice()
{
    /* discover devices */
    libusb_device **list;
    ssize_t count = libusb_get_device_list(context, &list);
    if (count < 0)
    {
        std::cout << "Error:  Unable to list USB devices currently attached to the system, " <<\
                     GetStrError(static_cast<libusb_error>(count)) << "\n";
        return nullptr;
    }

    /* iterate throw the devices' list */
    libusb_device *target = nullptr;
    for (ssize_t i = 0; i < count; i++)
    {
        /* Check vendor ID & Product ID */
        libusb_device_descriptor dev_desc;
        if (libusb_get_device_descriptor(list[i], &dev_desc))
            continue;
        if ((dev_desc.idVendor == this->vendor_id) && (dev_desc.idProduct == this->product_id))
        {
            target = list[i];
            target = libusb_ref_device(target);
            break;
        }
    }
    libusb_free_device_list(list, 1);

    if (!target)
    {
        std::cout << std::hex << std::setw(4) << std::setfill('0') << "Error:  Unable to find USB" \
                                                                      " device with idVendor: 0x" << this->vendor_id << " & idProduct: 0x" << \
                     this->product_id << "\n";

        return nullptr;
    }

    return target;
}


/**
 * @brief StandardUSB::GetUSBHandle
 * Opens the device previously found using GetUSBDevice
 * @param device a valid libusb_device pointer
 * @return libusb_device_handle * on success, nullptr otherwise
 */
libusb_device_handle *StandardUSB::GetUSBHandle(libusb_device *device)
{
    /* Open device */
    libusb_device_handle *handle = nullptr;
    int result = libusb_open(device, &handle);
    if(result < 0)
    {
        std::cout << "Error:  Unable to open USB device, " << \
                     GetStrError(static_cast<libusb_error>(result)) << "\n";
        return nullptr;
    }

    return handle;
}


/**
 * @brief StandardUSB::USBControlTransfer
 * Perform a USB control transfer.
 * The direction of the transfer is inferred from the bmRequestType field of the setup packet.
 * @param bmRequestType the request type field for the setup packet
 * @param bRequest the request field for the setup packet
 * @param wValue the value field for the setup packet
 * @param wIndex the index field for the setup packet
 * @param data a suitably-sized data buffer for either input or output
 * (depending on direction bits within bmRequestType)
 * @param wLength the length field for the setup packet. The data buffer should be at
 * least this size.
 * @return on success, the number of bytes actually transferred, libusb_error otherwise
 */
int StandardUSB::USBControlTransfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, \
                                    uint16_t wIndex, uint8_t *data, uint16_t wLength)
{
    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     bmRequestType,
                 /* bRequest      */     bRequest,
                 /* wValue        */     wValue,
                 /* wIndex        */     wIndex,
                 /* data          */     data,
                 /* length        */     wLength,
                 /* timeout       */     StandardUSB::time_out);

    return result;
}


/**
 * @brief StandardUSB::USBBulkTransfer
 * Perform a USB bulk transfer.
 * The direction of the transfer is inferred from the direction bits of the endpoint address.
 * For bulk reads, the length field indicates the maximum length of data you are expecting to
 * receive. If less data arrives than expected, this function will return the number of bytes
 * actually transferred.
 * You should also check the transferred parameter for bulk writes. Not all of the data may
 * have been written.
 * @param endpoint the address of a valid endpoint to communicate with
 * @param data a suitably-sized data buffer for either input or output (depending on endpoint)
 * @param length for bulk writes, the number of bytes from data to be sent. for bulk reads, the
 * maximum number of bytes to receive into the data buffer.
 * @return on success, the number of bytes actually transferred, libusb_error otherwise
 */
int StandardUSB::USBBulkTransfer(uint8_t endpoint, uint8_t *data, int length)
{
    int transferred = 0x00;

    int result =  libusb_bulk_transfer(this->usb_handle,
                  /* endpoint      */  endpoint,
                  /* data          */  data,
                  /* length        */  length,
                  /* transferred   */  &transferred,
                  /* timeout       */  StandardUSB::time_out);

    if ((!result) || (result == LIBUSB_ERROR_TIMEOUT))
        return transferred;

    return result;
}


/**
 * @brief StandardUSB::USBInterruptTransfer
 * Perform a USB interrupt transfer.
 * The direction of the transfer is inferred from the direction bits of the endpoint address.
 * For interrupt reads, the length field indicates the maximum length of data you are expecting
 * to receive. If less data arrives than expected, this function  will return the number of bytes
 * actually transferred.
 * You should also check the transferred parameter for interrupt writes. Not all of the data may
 * have been written.
 * The default endpoint bInterval value is used as the polling interval.
 * @param endpoint the address of a valid endpoint to communicate with
 * @param data a suitably-sized data buffer for either input or output (depending on endpoint)
 * @param length for interrupt writes, the number of bytes from data to be sent. for interrupt
 * reads, the maximum number of bytes to receive into the data buffer.
 * @return on success, the number of bytes actually transferred, libusb_error otherwise
 */
int StandardUSB::USBInterruptTransfer(uint8_t endpoint, uint8_t *data, int length)
{
    int transferred = 0x00;

    int result =  libusb_interrupt_transfer(this->usb_handle,
                  /* endpoint      */       endpoint,
                  /* data          */       data,
                  /* length        */       length,
                  /* transferred   */       &transferred,
                  /* timeout       */       StandardUSB::time_out);

    if ((!result) || (result == LIBUSB_ERROR_TIMEOUT))
        return transferred;

    return result;
}


/**
 * @brief StandardUSB::USBClaimInterface
 * Claim an interface.
 * You must claim the interface you wish to use before you can perform I/O on any of its endpoints.
 * Claiming of interfaces is a purely logical operation; it does not cause any requests to be sent
 * over the bus. Interface claiming is used to instruct the underlying operating system that your
 * application wishes to take ownership of the interface.
 * @param iterface 	the bInterfaceNumber of the interface you wish to claim
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::USBClaimInterface(int interface)
{
#ifdef __linux__
    /* check if a kernel driver is active on an interface */
    if(libusb_kernel_driver_active(this->usb_handle, interface) == 1)
    {
        int result = libusb_detach_kernel_driver(this->usb_handle, interface);
        if (result)
        {
            std::cout << "Error: Unable to detach kernel driver from interface: " << interface
                      << "\n";
            std::cout << "Error: Failed to claim interface: " << interface << \
                         " ," << GetStrError(static_cast<libusb_error>(result)) <<"\n";
            return result;
        }
    }
#endif

    int result = libusb_claim_interface(this->usb_handle, interface);
    if(result < 0)
    {
        std::cout<< "Error: Unable to claim interface: " << interface <<\
                    " ," << GetStrError(static_cast<libusb_error>(result)) <<"\n";
        return result;
    }

    return 0;
}


/**
 * @brief StandardUSB::USBReleaseInterface
 * Release an interface previously claimed with USBClaimInterface.
 * You should release all claimed interfaces before closing the usb device.
 * A SET_INTERFACE control request will be sent to the device, resetting interface state to the
 * first alternate setting.
 * @param iterface the bInterfaceNumber of the interface you wish to release
 * @return
 */
int StandardUSB::USBReleaseInterface(int interface)
{
    libusb_release_interface(this->usb_handle, interface);

    return 0;
}


/**
 * @brief StandardUSB::USBReset
 * Perform a USB port reset to reinitialize a device.
 * This means that the device handle is no longer valid you should close it and rediscover the
 * device
 * @return
 */
int StandardUSB::USBReset()
{
    libusb_reset_device(this->usb_handle);
    return 0;
}


#endif //STANDARD_USB
