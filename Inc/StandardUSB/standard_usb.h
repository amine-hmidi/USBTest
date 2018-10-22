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

#ifndef USB_H
#define USB_H


/* C++ Includes */
#include <string>

/* C Includes */

/* User Includes */
#include "display_manager.h"


/* Forward declarations of libusb types */
struct libusb_device;
struct libusb_device_handle;
struct libusb_device_descriptor;
struct libusb_config_descriptor;
struct libusb_context;


class StandardUSB
{
public:

    /* USB Device Class supported in this firmware */
    enum USBClassType
    {
        /* the interface is not aware of the usb device class */
        NONE,
        /* DFU 1.1 */
        DFU_1_1,
        /* DFU1.1 St Extension */
        DFU_ST_EX
    };

    /* ****************************************************************************************** */
    /* ****************************** Class Constructor/Destructor ****************************** */
    /* ****************************************************************************************** */
    StandardUSB(uint16_t vendor_id, uint16_t product_id);
    virtual ~StandardUSB();
    StandardUSB() = delete;
    StandardUSB (const StandardUSB &) = delete;
    StandardUSB& operator = (const StandardUSB &) = delete;
    StandardUSB (const StandardUSB &&) = delete;
    StandardUSB& operator = (StandardUSB &&) = delete;

    /* ****************************************************************************************** */
    /* ************************************* USB Attributes ************************************* */
    /* ****************************************************************************************** */
    static void CtrTimeOut(unsigned int t_ms)  { StandardUSB::ctr_time_out = t_ms;}
    static void BulkTimeOut(unsigned int t_ms)  { StandardUSB::bulk_time_out = t_ms;}
    static void IntTimeOut(unsigned int t_ms)  { StandardUSB::interr_time_out = t_ms;}
    StandardUSB::USBClassType DeviceClass() const {return this->usb_class;}
    uint16_t IdProduct() const {return this->product_id;}
    uint16_t IdVendor() const {return this->vendor_id;}

    /* ****************************************************************************************** */
    /* ************************** Device Handling/Discovering Functions ************************* */
    /* ****************************************************************************************** */
    static void ListUSBDevices();
    virtual int8_t OpenDevice();
    virtual int8_t CloseDevice();
    virtual int8_t ReOpenDevice();
    int USBControlTransfer(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, \
                           uint16_t wIndex, uint8_t *data, uint16_t wLength);
    int USBBulkTransfer(uint8_t endpoint, uint8_t *data, int length);
    int USBInterruptTransfer(uint8_t endpoint, uint8_t *data, int length);
    int USBClaimInterface(int iterface);
    int USBReleaseInterface(int iterface);
    int USBReset();

    /* ****************************************************************************************** */
    /* ********************************* Standard Device Requests ******************************* */
    /* ****************************************************************************************** */
    int DeviceGetStatus(uint16_t &status);
    int DeviceClearFeature(uint16_t feature);
    int DeviceSetFeature(uint16_t feature);
    int DeviceSetAddress(uint16_t address);
    int DeviceGetDescriptor(uint8_t type, uint8_t index, uint16_t language, uint8_t *data, \
                            uint16_t length);
    int DeviceSetDescriptor(uint8_t type, uint8_t index, uint16_t language, uint8_t *data, \
                            uint16_t length);
    int DeviceGetCongiguration(uint8_t &data);
    int DeviceSetCongiguration(uint16_t configuration);
    std::string GetStringDescriptor(uint8_t index, uint16_t language);

    /* ****************************************************************************************** */
    /* ******************************** Standard Interface Requests ***************************** */
    /* ****************************************************************************************** */
    int InterfaceGetStatus(uint16_t interface, uint16_t &status);
    int InterfaceClearFeature(uint16_t interface, uint16_t feature);
    int InterfaceSetFeature(uint16_t interface, uint16_t feature);
    int InterfaceGetAltSetting(uint16_t interface, uint8_t &alt_setting);
    int InterfaceSetAltSetting(uint16_t interface, uint8_t alt_setting);

    /* ****************************************************************************************** */
    /* ********************************* Standard Endpoint Requests ***************************** */
    /* ****************************************************************************************** */
    int EndpointGetStatus(uint16_t endpoint, uint16_t &status);
    int EndpointClearFeature(uint16_t endpoint, uint16_t feature);
    int EndpointSetFeature(uint16_t endpoint, uint16_t feature);
    int EndpointSynchFrame(uint16_t endpoint, uint16_t &frame);

    /* ****************************************************************************************** */
    /* *********************************** Messaging Functions ********************************** */
    /* ****************************************************************************************** */
    static std::string GetStrError(int error);
    virtual void DisplayDescriptorsSet();

protected:

    /* usb device */
    libusb_device *usb_device = nullptr;
    /* usb handle */
    libusb_device_handle *usb_handle = nullptr;
    /* usb device descriptor */
    libusb_device_descriptor *usb_device_descriptor = nullptr;
    /* usb configuration descriptor */
    libusb_config_descriptor *usb_config_descriptor = nullptr;
    /* usb device class */
    USBClassType usb_class = USBClassType::NONE;
    /* contol transfer timeout in ms */
    static unsigned int ctr_time_out;
    /* bulk transfer timeout in ms */
    static unsigned int bulk_time_out;
    /* interr transfer timeout in ms */
    static unsigned int interr_time_out;
    /* Display manager */
    static DisplayManager *usb_dm;

    /* ****************************************************************************************** */
    /* *********************************** Descriptors Requests ********************************* */
    /* ****************************************************************************************** */
    libusb_device_descriptor *GetDeviceDescriptor();
    libusb_config_descriptor *GetConfigurationDescriptor(uint8_t index);

    /* ****************************************************************************************** */
    /* *********************************** Messaging Functions ********************************** */
    /* ****************************************************************************************** */
    void DisplayDeviceDescriptor();
    void DisplayConfigurationDescriptor(bool display_extra = false);

private:

    /* Product ID */
    uint16_t vendor_id = 0x00;
    /* Manif. ID */
    uint16_t product_id = 0x00;
    /* libusb context */
    libusb_context *context;

    /* ****************************************************************************************** */
    /* ******************************** Device Handling Functions ******************************* */
    /* ****************************************************************************************** */
    libusb_device *GetUSBDevice();
    libusb_device_handle *GetUSBHandle(libusb_device *device);

    /* ****************************************************************************************** */
    /* *********************************** Messaging Functions ********************************** */
    /* ****************************************************************************************** */
    void DisplayInterfaceDescriptor(const struct libusb_interface &interface, \
                                    bool display_extra = false);
    void DisplayInterfaceAltDescriptor(const struct libusb_interface_descriptor &altsetting, \
                                       bool display_extra = false);
    void DisplayEndpointDescriptor(const struct libusb_endpoint_descriptor &endpoint, \
                                   bool display_extra = false);

};

#endif // USB_H


#endif //STANDARD_USB
