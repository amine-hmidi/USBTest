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

#if defined (USB_IN_DFU_MODE)

#ifndef DFU_CLASS_H
#define DFU_CLASS_H

/* C++ Includes */
#include <string>

/* C Includes */

/* User Includes */
#include "standard_usb.h"



class DFUClass : public StandardUSB
{
public:

    /*  DFU Functional Descriptor */
    typedef struct DFUFunctionalDescriptor
    {
        DFUFunctionalDescriptor()
        {
            this->bLength = 0x00;
            this->bDescriptorType = 0x00;
            this->bmAttributes = 0x00;
            this->wDetachTimeOut = 0x00;
            this->wTransferSize = 0x00;
            this->bcdDFUVersion = 0x00;
        }

        void Clear()
        {
            this->bLength = 0x00;
            this->bDescriptorType = 0x00;
            this->bmAttributes = 0x00;
            this->wDetachTimeOut = 0x00;
            this->wTransferSize = 0x00;
            this->bcdDFUVersion = 0x00;
        }

        /* Descriptor length */
        uint8_t bLength;

        /* Descriptor type must be 0x21 */
        uint8_t bDescriptorType;

        /* DFU attributes */
        uint8_t bmAttributes;

        /*
         * Time, in milliseconds, that the device
         * will wait after receipt of the
         * DFU_DETACH request
        */
        uint16_t wDetachTimeOut;

        /*
         * Maximum number of bytes that the
         * device can accept per control-write
         * transaction
        */
        uint16_t wTransferSize;

        /*
         * Numeric expression identifying the
         * version of the DFU
        */
        uint16_t bcdDFUVersion;

    } DFUFunctionalDescriptor;


    /* DFU Class-Specific Request Values (DFU bRequest) */
    enum DFUbRequest
    {
        DFU_DETACH          = 0x00,

        DFU_DNLOAD          = 0x01,

        DFU_UPLOAD          = 0x02,

        DFU_GETSTATUS       = 0x03,

        DFU_CLRSTATUS       = 0x04,

        DFU_GETSTATE        = 0x05,

        DFU_ABORT           = 0x06
    };

    /* DFU bmRequestType */
    enum DFUbmRequestType
    {
        /* device-to-host */
        DFU_REQUEST_IN          = (0x80|(0x01 << 5)|0x01),

        /* host-to-device */
        DFU_REQUEST_OUT         = (0x00|(0x01 << 5)|0x01)
    };

    /* DFU device status */
    enum DFUStatus
    {
        /* No error condition is present */
        OK              = 0x00,

        /* File is not targeted for use by this device */
        errTARGET       = 0x01,

        /* File is for this device but fails some vendor-specific
         * verification test. */
        errFILE         = 0x02,

        /* Device is unable to write memory */
        errWRITE        = 0x03,

        /* Memory erase function failed. */
        errERASE        = 0x04,

        /* Memory erase check failed */
        errCHECK_ERASED = 0x05,

        /* Program memory function failed */
        errPROG         = 0x06,

        /* Programmed memory failed verification */
        errVERIFY       = 0x07,

        /* Cannot program memory due to received address that is
         * out of range */
        errADDRESS      = 0x08,

        /* Received DFU_DNLOAD with wLength = 0, but device does
         * not think it has all of the data yet */
        errNOTDONE      = 0x09,

        /* Device’s firmware is corrupt. It cannot return to run-time
         * (non-DFU) operations */
        errFIRMWARE     = 0x0A,

        /* iString indicates a vendor-specific error */
        errVENDOR       = 0x0B,

        /* Device detected unexpected USB reset signaling */
        errUSBR         = 0x0C,

        /* Device detected unexpected power on reset */
        errPOR          = 0x0D,

        /* Something went wrong, but the device does not know what it
         * was */
        errUNKNOWN      = 0x0E,

        /* Device stalled an unexpected request */
        errSTALLEDPKT   = 0x0F,

        /* Unkown */
        statusUNKNOWN   = 0xFF
    };

    /* DFU device state */
    enum DFUState
    {
        /* Device is running its normal application */
        appIDLE                 = 0x00,

        /* Device is running its normal application, has received the
         * DFU_DETACH request, and is waiting for a USB reset */
        appDETACH               = 0x01,

        /* Device is operating in the DFU mode and is waiting for
         * requests */
        dfuIDLE                 = 0x02,

        /* Device has received a block and is waiting for the host to
         * solicit the status via DFU_GETSTATUS */
        dfuDNLOAD_SYNC          = 0x03,

        /* Device is programming a control-write block into its
         * nonvolatile memories */
        dfuDNBUSY               = 0x04,

        /* Device is processing a download operation. Expecting
         * DFU_DNLOAD requests */
        dfuDNLOAD_IDLE          = 0x05,

        /* Device has received the final block of firmware from the host
         * and is waiting for receipt of DFU_GETSTATUS to begin the
         * Manifestation phase; or device has completed the
         * Manifestation phase and is waiting for receipt of
         * DFU_GETSTATUS. (Devices that can enter this state after
         * the Manifestation phase set bmAttributes bit
         * bitManifestationTolerant to 1.) */
        dfuMANIFEST_SYNC        = 0x06,

        /* Device is in the Manifestation phase. (Not all devices will be
         * able to respond to DFU_GETSTATUS when in this state.) */
        dfuMANIFEST             = 0x07,

        /* Device has programmed its memories and is waiting for a
         * USB reset or a power on reset. (Devices that must enter
         * this state clear bitManifestationTolerant to 0.) */
        dfuMANIFEST_WAIT_RESET  = 0x08,

        /* The device is processing an upload operation. Expecting
         * DFU_UPLOAD requests. */
        dfuUPLOAD_IDLE          = 0x09,

        /* An error has occurred. Awaiting the DFU_CLRSTATUS
         * request */
        dfuERROR                = 0xA,

        /* Unknown State */
        stateUNKNOWN            = 0xFF
    };

    /* DFU_GETSTATUS request payload */
    typedef struct Status
    {
        Status()
        {
            this->bStatus = statusUNKNOWN;
            this->bState = stateUNKNOWN;
            this->bwPollTimeOut = 0x00;
            this->iString = 0x00;
        }

        void Clear()
        {
            this->bStatus = statusUNKNOWN;
            this->bState = stateUNKNOWN;
            this->bwPollTimeOut = 0x00;
            this->iString = 0x00;
        }

        /* An indication of the status resulting from the
         * execution of the most recent request. */
        DFUClass::DFUStatus bStatus;

        /* Minimum time, in milliseconds, that the host
         * should wait before sending a subsequent
         * DFU_GETSTATUS request */
        uint32_t bwPollTimeOut;

        /* An indication of the state that the device is going to
         * enter immediately following transmission of this
         * response. (By the time the host receives this
         * information, this is the current state of the device.)  */
        DFUClass::DFUState bState;

        /* Index of status description in string table */
        uint8_t iString;
    }Status;

    /* ****************************************************************************************** */
    /* ******************************* Class Constructor/Destructor ***************************** */
    /* ****************************************************************************************** */
    DFUClass(uint16_t vendor_id, uint16_t product_id);
    virtual ~DFUClass(){}

    /* ****************************************************************************************** */
    /* ************************** Device Handling/Discovering Functions ************************* */
    /* ****************************************************************************************** */
    virtual int8_t OpenDevice();
    virtual int8_t CloseDevice();
    virtual int8_t ReOpenDevice();

    /* ****************************************************************************************** */
    /* *********************************** Descriptors Requests ********************************* */
    /* ****************************************************************************************** */
    int GetDFUInterface();
    const DFUClass::DFUFunctionalDescriptor *GetDFUFunctionalDescriptor();

    /* ****************************************************************************************** */
    /* ************************************* DFU1.1 Requests ************************************ */
    /* ****************************************************************************************** */
    const DFUClass::Status DfuGetStatus();
    DFUClass::DFUState DfuGetState();
    int DfuClearStatus();
    int DfuAbort();
    int DfuDetach();
    int DfuDownloadPacket(uint16_t wBlockNum, const uint8_t *data, uint16_t length);
    int DfuDownloadZero(uint16_t wBlockNum);
    int DfuUploadPacket(uint16_t wBlockNum, uint8_t *data, uint16_t length);
    int DfuDownload(uint16_t wBlockNum, const uint8_t *data, uint32_t length);
    int DfuUpload(uint16_t wBlockNum, uint8_t *data, uint32_t length);

    /* ****************************************************************************************** */
    /* *********************************** Messaging Functions ********************************** */
    /* ****************************************************************************************** */
    virtual void DisplayDescriptorsSet();
    void DisplayDFUFunctionalDescriptor();
    void DisplayDfuStatus();
    void DisplayDfuState();


protected:

    /* DFU Functional Descriptor */
    struct DFUClass::DFUFunctionalDescriptor dfu_func_desc;
    /* DFU Device Status */
    struct DFUClass::Status dfu_status;
    /* DFu Device state */
    DFUState dfu_state = stateUNKNOWN;
    /* device can upload */
    uint8_t can_upload = 0x00;
    /* device can download */
    uint8_t can_download = 0x00;
    /* device manifestation tolerant */
    uint8_t manif_tolerant = 0x00;
    /* device will detach */
    uint8_t will_detach = 0x00;
    /* detach timeout */
    uint16_t wDetachTimeOut = 0x00;
    /* control transfert size */
    uint16_t wTransferSize = 0x00;
    /* the dfu interface index */
    int dfu_interface = 0xFFF;

    /* ****************************************************************************************** */
    /* *********************************** Messaging Functions ********************************** */
    /* ****************************************************************************************** */
    std::string GetStatusStr(DFUClass::DFUStatus status);
    std::string GetStateStr(DFUClass::DFUState status);

};

#endif // DFU_CLASS_H

#endif
