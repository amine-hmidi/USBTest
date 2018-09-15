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


/* ********************************************************************************************** */
/* *********************************** Standard Device Requests ********************************* */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::DeviceGetStatus
 * Send a standard device get status request.
 * Upon success the output parameter will be populated
 * with the retrieved data;
 * @param status device status
 * @return 0 on success, libusb_error code otherwise
 */
int StandardUSB::DeviceGetStatus(uint16_t &status)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);
    uint8_t data[2] = {0x00};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_GET_STATUS,
                 /* wValue        */     0x00,
                 /* wIndex        */     0x00,
                 /* data          */     data,
                 /* length        */     0x02,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to request USB device status, " << \
                     GetStrError(static_cast<libusb_error>(result)) << "\n";
        return result;
    }

    if(result != 2)
    {
        std::cout << "Error:  USB get device status error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x02)\n";
        return -99;
    }

    status = static_cast<uint16_t>(data[0] |\
             (static_cast<uint32_t>(data[1]) << 8));

    return 0;
}


/**
 * @brief StandardUSB::DeviceClearFeature
 * Send a standard device clear feature request.
 * @param feature feature to be descativated
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::DeviceClearFeature(uint16_t feature)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_CLEAR_FEATURE,
                 /* wValue        */     feature,
                 /* wIndex        */     0x00,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Clear USB device Feature: 0x" << std::hex   \
                  << std::setw(4) << std::setfill('0') <<  static_cast<uint32_t>(feature) \
                  << " ," << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result)
    {
        std::cout << "Error:  USB clear device feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::DeviceSetFeature
 * Send a standard device set feature request.
 * @param feature feature to be activated
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::DeviceSetFeature(uint16_t feature)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_SET_FEATURE,
                 /* wValue        */     feature,
                 /* wIndex        */     0x00,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Set USB device Feature: 0x" << std::hex  \
                  <<  std::setw(4) << std::setfill('0') << static_cast<uint32_t>(feature) \
                  << " ," << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result)
    {
        std::cout << "Error:  USB set device feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::DeviceSetAddress
 * Send a standard device set address request
 * @param address device new address
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::DeviceSetAddress(uint16_t address)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_SET_ADDRESS,
                 /* wValue        */     address,
                 /* wIndex        */     0x00,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Set USB device Address: 0x"  << std::hex \
                  << std::setw(4) << std::setfill('0') << static_cast<uint32_t>(address)\
                  << " ," << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result)
    {
        std::cout << "Error:  USB set device address error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::DeviceGetDescriptor
 * Send a standard device get descriptor request.
 * @param type descriptor type
 * @param index descriptor index
 * @param language language code (0x409 for USB english)
 * @param data buffer to store received data
 * @param length max length of data buffer
 * @return the actual nbr of bytes received on success, libusb_error otherwise
 */
int StandardUSB::DeviceGetDescriptor(uint8_t type, uint8_t index, uint16_t language, uint8_t *data,\
                                     uint16_t length)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_GET_DESCRIPTOR,
                 /* wValue        */     static_cast<uint16_t>((static_cast<uint32_t>(type) << 8)\
                                                               | (static_cast<uint32_t>(index))),
                 /* wIndex        */     language,
                 /* data          */     data,
                 /* length        */     length,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
        std::cout << "Error:  Unable to Get USB Descriptor with type: 0x"  << std::hex \
                  << std::setw(4) << std::setfill('0') << static_cast<uint32_t>(type) \
                  << " ,index: 0x" << static_cast<uint32_t>(index) <<" ,language: 0x" \
                  << static_cast<uint32_t>(language) <<  " ," \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

    return result;
}


/**
 * @brief StandardUSB::DeviceSetDescriptor
 * Send a standard device set descriptor request.
 * @param type descriptor type
 * @param index descriptor index
 * @param language language code (0x409 for USB english)
 * @param data buffer containing the new descriptor's fields values
 * @param length the data buffer length
 * @return the actual nbr of bytes sent  on success, libusb_error otherwise
 */
int StandardUSB::DeviceSetDescriptor(uint8_t type, uint8_t index, uint16_t language, uint8_t *data,\
                                     uint16_t length)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_SET_DESCRIPTOR,
                 /* wValue        */     static_cast<uint16_t>((static_cast<uint32_t>(type) << 8) \
                                                               | (static_cast<uint32_t>(index))),
                 /* wIndex        */     language,
                 /* data          */     data,
                 /* length        */     length,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
        std::cout << "Error:  Unable to Set USB Descriptor with type: 0x"  << std::hex \
                  << std::setw(4) << std::setfill('0') << static_cast<uint32_t>(type) \
                  << " ,index: 0x" << static_cast<uint32_t>(index) <<" ,language: 0x" \
                  << static_cast<uint32_t>(language) << " ," \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

    return result;
}


/**
 * @brief StandardUSB::DeviceGetCongiguration
 * Send a standard device get configuration request.
 * Upon success the output parameter will be populated with
 * the current usb device configuration.
 * @param data output parameter
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::DeviceGetCongiguration(uint8_t &data)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);
    uint8_t l_data[1] = {0x00};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_GET_CONFIGURATION,
                 /* wValue        */     0x00,
                 /* wIndex        */     0x00,
                 /* data          */     l_data,
                 /* length        */     1,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Get USB Configuration ,"  << std::hex << std::setw(4) \
                  << std::setfill('0') << GetStrError(static_cast<libusb_error>(result)) << "\n";
        return  result;
    }

    if(result != 1)
    {
        std::cout << "Error:  USB get device configuration error, Unexpected nbr of byte "\
                  << " transfered (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x01)\n";
        return -99;
    }

    data = (*l_data);

    return 0;
}


/**
 * @brief StandardUSB::DeviceSetCongiguration
 * Send a standard device set configuration request.
 * @param configuration the configuration index to which the device should switch
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::DeviceSetCongiguration(uint16_t configuration)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_DEVICE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_SET_CONFIGURATION,
                 /* wValue        */     configuration,
                 /* wIndex        */     0x00,
                 /* data          */     nullptr,
                 /* length        */     0,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Set USB Configuration 0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') << static_cast<uint32_t>(configuration) << " ," \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result != 1)
    {
        std::cout << "Error:  USB set device configuration error, Unexpected nbr of byte "\
                  << " transfered (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/* ********************************************************************************************** */
/* ********************************** Standard Interface Requests ******************************* */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::InterfaceGetStatus
 * Send a standard usb interface get status request.
 * Upon success the output parameter 'status' will be populated the interface's status
 * @param interface the index of the interface to which the request will be sent
 * @param status output parameter
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::InterfaceGetStatus(uint16_t interface, uint16_t &status)
{
    uint8_t req_type = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_INTERFACE);
    uint8_t data[2] = {0x00};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_type,
                 /* bRequest      */     LIBUSB_REQUEST_GET_STATUS,
                 /* wValue        */     0x00,
                 /* wIndex        */     interface,
                 /* data          */     data,
                 /* length        */     0x02,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to request USB Interface :0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') << static_cast<uint32_t>(interface) << " status, " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";
        return result;
    }

    if(result != 2)
    {
        std::cout << "Error:  USB get interface status error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x02)\n";
        return -99;
    }

    status = static_cast<uint16_t>(data[0] |\
             (static_cast<uint32_t>(data[1]) << 8));

    return 0;
}


/**
 * @brief StandardUSB::InterfaceClearFeature
 * Send a standard usb interface clear feature request.
 * @param interface the index of the interface to which the request will be sent
 * @param feature the index of the feature to be disactivated
 * @return 0 on success, libusb_error otherswise
 */
int StandardUSB::InterfaceClearFeature(uint16_t interface, uint16_t feature)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_INTERFACE);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_CLEAR_FEATURE,
                 /* wValue        */     feature,
                 /* wIndex        */     interface,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Clear USB Interface :0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') << static_cast<uint32_t>(interface) << " , feature: 0x" \
                  << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(feature) << ", " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result)
    {
        std::cout << "Error:  USB clear interface feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::InterfaceSetFeature
 * Send a standard usb interface set feature request.
 * @param interface the index of the interface to which the request will be sent
 * @param feature the index of the feature to be disactivated
 * @return 0 on success, libusb_error otherswise
 */
int StandardUSB::InterfaceSetFeature(uint16_t interface, uint16_t feature)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_INTERFACE);

    int result = libusb_control_transfer(this->usb_handle,\
                  /* bmRequestType */     req_t,
                  /* bRequest      */     LIBUSB_REQUEST_SET_FEATURE,
                  /* wValue        */     feature,
                  /* wIndex        */     interface,
                  /* data          */     nullptr,
                  /* length        */     0x00,
                  /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Set USB Interface :0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') << static_cast<uint32_t>(interface) << " , feature: 0x" \
                  << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(feature) << ", " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result != 1)
    {
        std::cout << "Error:  USB set interface feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::InterfaceGetAltSetting
 * Send a standard usb interface get current alternate setting request.
 * Upon success the output parameter 'alt_setting' will be populated will the recieved data
 * @param interface the index of the interface to which the request will be sent
 * @param alt_setting output parameter
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::InterfaceGetAltSetting(uint16_t interface, uint8_t &alt_setting)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_INTERFACE);
    uint8_t l_data[1] = {0x00};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_GET_INTERFACE,
                 /* wValue        */     0x00,
                 /* wIndex        */     interface,
                 /* data          */     l_data,
                 /* length        */     0x01,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Get USB Interface :0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') <<    static_cast<uint32_t>(interface) \
                  << " alternate setting nbr, " << GetStrError(static_cast<libusb_error>(result)) \
                  << "\n";

        return result;
    }

    if(result != 1)
    {
        std::cout << "Error:  USB get interface alt setting error, Unexpected nbr of byte "\
                  << " transfered (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x01)\n";
        return -99;
    }

    alt_setting = (*l_data);

    return 0;
}


/**
 * @brief StandardUSB::InterfaceSetAltSetting
 * Send a standard us interface set alternate setting request.
 * @param interface the index of the interface to which the request will be sent
 * @param alt_setting the index of the alternate setting to be activated
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::InterfaceSetAltSetting(uint16_t interface, uint8_t alt_setting)
{
    /*
     * using the libusb function has the advantage of telling the host OS that we
     * changed the interface alternate setting
     */
    int result = libusb_set_interface_alt_setting(this->usb_handle, interface, alt_setting);
    if(result < 0)
        std::cout << "Error:  Unable to Set USB Interface :0x"  << std::hex << std::setw(4) \
                  << std::setfill('0') << static_cast<uint32_t>(interface) \
                  << " alternate setting nbr :0x" << std::hex << std::setw(4) \
                  << static_cast<uint32_t>(alt_setting) <<  " ," \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

    return result;
}


/* ********************************************************************************************** */
/* *********************************** Standard Endpoint Requests ******************************* */
/* ********************************************************************************************** */
/**
 * @brief StandardUSB::EndpointGetStatus
 * Send a standard usb endpoint get status request.
 * Upon success the output parameter 'status' will be populated the endpoint's status
 * @param endpoint index of the endpoint
 * @param status output parameter
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::EndpointGetStatus(uint16_t endpoint, uint16_t &status)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_ENDPOINT);
    uint8_t data[2] = {0x00};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_GET_STATUS,
                 /* wValue        */     0x00,
                 /* wIndex        */     endpoint,
                 /* data          */     data,
                 /* length        */     0x02,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to request USB endpoint status :0x"  << std::hex  \
                  << std::setw(4) << std::setfill('0') <<  static_cast<uint32_t>(endpoint) \
                  << " status, " << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result != 1)
    {
        std::cout << "Error:  USB get endpoint status error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x02)\n";
        return -99;
    }

    status = static_cast<uint16_t>(data[0] |\
             (static_cast<uint32_t>(data[1]) << 8));

    return 0;
}


/**
 * @brief StandardUSB::EndpointClearFeature
 * Send a standard usb endpoint clear feature request.
 * @param endpoint index of the endpoint
 * @param feature featute to be disabled
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::EndpointClearFeature(uint16_t endpoint, uint16_t feature)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_ENDPOINT);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_CLEAR_FEATURE,
                 /* wValue        */     feature,
                 /* wIndex        */     endpoint,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to clear USB endpoint feature:0x"  << std::hex << std::setw(4)\
                  << std::setfill('0') << static_cast<uint32_t>(endpoint) << std::hex \
                  << std::setw(4) << std::setfill('0') << " , feature: 0x" \
                  << static_cast<uint32_t>(feature) << ", " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";
    }

    if(result)
    {
        std::cout << "Error:  USB clear endpoint feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }


    return 0;
}


/**
 * @brief StandardUSB::EndpointSetFeature
 * Send a standard usb endpoint set feature request.
 * @param endpoint index of the endpoint
 * @param feature feature to be enabled
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::EndpointSetFeature(uint16_t endpoint, uint16_t feature)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_ENDPOINT);

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_SET_FEATURE,
                 /* wValue        */     feature,
                 /* wIndex        */     endpoint,
                 /* data          */     nullptr,
                 /* length        */     0x00,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to set USB endpoint feature:0x"  << std::hex << std::setw(4)\
                  << std::setfill('0') << static_cast<uint32_t>(endpoint) << std::hex \
                  << std::setw(4) << std::setfill('0') << " , feature: 0x" \
                  << static_cast<uint32_t>(feature) << ", " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result)
    {
        std::cout << "Error:  USB set endpoint feature error, Unexpected nbr of byte transfered"\
                  << " (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x00)\n";
        return -99;
    }

    return 0;
}


/**
 * @brief StandardUSB::EndpointSynchFrame
 * Send a standard usb endpoint synchronize frame request.
 * @param endpoint index of the endpoint
 * @param frame frame index
 * @return 0 on success, libusb_error otherwise
 */
int StandardUSB::EndpointSynchFrame(uint16_t endpoint, uint16_t frame)
{
    uint8_t req_t = (LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_STANDARD|LIBUSB_RECIPIENT_ENDPOINT);
    uint8_t data[2] = {static_cast<uint8_t>(frame & 0xFF),
                       static_cast<uint8_t>((frame >> 8) & 0xFF)};

    int result = libusb_control_transfer(this->usb_handle,\
                 /* bmRequestType */     req_t,
                 /* bRequest      */     LIBUSB_REQUEST_SYNCH_FRAME,
                 /* wValue        */     0x00,
                 /* wIndex        */     endpoint,
                 /* data          */     data,
                 /* length        */     0x02,
                 /* timeout       */     StandardUSB::time_out);

    if(result < 0)
    {
        std::cout << "Error:  Unable to Synchronize Frame Endpoint :0x"  << std::hex \
                  << std::setw(4) << std::setfill('0') << static_cast<uint32_t>(endpoint) << ", " \
                  << GetStrError(static_cast<libusb_error>(result)) << "\n";

        return result;
    }

    if(result != 2)
    {
        std::cout << "Error:  USB endpoint synchronize frame error, Unexpected nbr of byte "\
                  << "transfered (0x" << std::hex << std::setw(4) << std::setfill('0') \
                  << static_cast<uint32_t>(result) << " , expected 0x02)\n";
        return -99;
    }

    return 0;
}


#endif //STANDARD_USB
