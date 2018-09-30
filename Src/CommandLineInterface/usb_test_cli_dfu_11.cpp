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
#include <string>
#include <cstdlib>
#include <climits>

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


/* ********************************************************************************************** */
/* ***************************************** CLI Parser ***************************************** */
/* ********************************************************************************************** */

void USBTestCli::InitDFU11Commands()
{
    options->add_options("DFU 1.1 Options")
            ("dfu", "Connect as a USB in DFU mode")
            ("dfu_getstatus", "Request the DFU device status")
            ("dfu_getstate", "Request the DFU device state")
            ("dfu_clearstatus", "Send a DFU device clear status request")
            ("dfu_abort", "Send a DFU device abort request")
            ("dfu_detach", "Send a DFU device detach request")
            ("dfu_dnload", "Send a DFU download request")
            ("dfu_upload", "Send a DFU upload request")
            ("wBlockNum", "The packet number from which the download/upload will start",\
             cxxopts::value<uint16_t>())
            ;
}

void USBTestCli::DisplayDFU11Help()
{
    std::cout << "DFU 1.1 options\n";
    /* **** */
    std::cout << "\t    --dfu                   Connect as USB in DFU mode (must use --idvendor\n";
    std::cout << "\t                            and --idproduct usb options) \n";
    std::cout << "\t    --dfu_getstatus         Request the DFU device status\n";
    std::cout << "\t    --dfu_getstate          Request the DFU device state\n";
    std::cout << "\t    --dfu_clearstatus       Send a DFU device clear status request\n";
    std::cout << "\t    --dfu_abort             Send a DFU device abort request\n";
    std::cout << "\t    --dfu_detach            Send a DFU device detach request\n";
    std::cout << "\t    --dfu_dnload            Send a DFU download request\n";
    std::cout << "\t    --dfu_upload            Send a DFU upload request\n";
    std::cout << "\t    --wBlockNum             The packet number from which the download/upload\n";
    std::cout << "\t                            operation will start\n";
}

void USBTestCli::ParseDFU11Cmds(const cxxopts::ParseResult &result)
{
    if(result.count("dfu"))
    {
        std::cout << "\n";
        std::cout << "Info: Establishing connection with target device:\n";
        /* Check if both idvendor and idproduct are present */
        if(!result.count("idvendor"))
        {
            std::cout << "Error: Missing --idvendor option\n";
            return;
        }

        if(!result.count("idproduct"))
        {
            std::cout << "Error: Missing --idproduct option\n";
            return;
        }

        /* get idvendor, idproduct */
        uint16_t idvendor = result["idvendor"].as<uint16_t>();
        uint16_t idproduct = result["idproduct"].as<uint16_t>();

        /* init the dfu device objects */
        ConnectDFU11(idvendor, idproduct);
    }

    if (!this->usb_device)
        return;

    if (this->usb_device->DeviceClass() != StandardUSB::USBClassType::DFU_1_1)
        return;

    DFUClass *dfu_device = dynamic_cast<DFUClass *>(usb_device);

    DFU11GetStatus(result, dfu_device);
    DFU11GetState(result, dfu_device);
    DFU11ClearStatus(result, dfu_device);
    DFU11Abort(result, dfu_device);
    DFU11Detach(result, dfu_device);
}


void USBTestCli::ConnectDFU11(uint16_t idVendor, uint16_t idProduct)
{
    /* init the usb device objects */
    if (usb_device)
    {
        delete usb_device;
        usb_device = nullptr;
    }

    usb_device = new(std::nothrow) DFUClass(idVendor, idProduct);
    if (!usb_device)
    {
        std::cout << "Error: Unable to initialize the usb device, Mmeory allocation error\n";
        return;
    }

    /* open the usb device */
    DFUClass *dfu_device = dynamic_cast<DFUClass *>(usb_device);
    if (dfu_device->OpenDevice())
    {
        delete usb_device;
        usb_device = nullptr;
        return;
    }

    std::cout << "Info: Connection established\n";
}


void USBTestCli::DFU11GetStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_getstatus"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU get status:\n";

    DFUClass::Status status = dfu_device->DfuGetStatus();
    if ((status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) &&
        (status.bState == DFUClass::DFUState::stateUNKNOWN))
        return;

    dfu_device->DisplayDfuStatus();
}


void USBTestCli::DFU11GetState(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_getstate"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU get state:\n";

    DFUClass::DFUState state = dfu_device->DfuGetState();
    if (state == DFUClass::DFUState::stateUNKNOWN)
        return;

    dfu_device->DisplayDfuState();
}


void USBTestCli::DFU11ClearStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_clearstatus"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU clear status:\n";

    if (dfu_device->DfuClearStatus())
        return;

    std::cout << "Info: DFU clear status Done\n";
}


void USBTestCli::DFU11Abort(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_abort"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU abort:\n";

    if (dfu_device->DfuAbort())
        return;

    std::cout << "Info: DFU abort Done\n";
}


void USBTestCli::DFU11Detach(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_detach"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU detach:\n";

    if (dfu_device->DfuDetach())
        return;

    std::cout << "Info: DFU detach Done\n";
}


void USBTestCli::DFU11Download(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_dnload"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU download:\n";

    uint16_t wBlockNum = 0;
    if (!result.count("wBlockNum"))
    {
        std::cout << "Warning: Missing --wBlockNum option, assuming wBlockNum is 0\n";
    }
    else
    {
        wBlockNum = result["wBlockNum"].as<uint16_t>();
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    /* 1, 2, 4 or 8 bytes pointer data
     * ignore --file, check --size options if any
     */
    if(result.count("data8") || result.count("data16") || result.count("data32") ||\
            result.count("data64"))
    {
        data = GetDataCli(result, size);
        if (!data)
            return;
    }
    /* null data */
    else if (result.count("data0"))
    {
        data = nullptr;
        size = 0x00;
    }
    /* data will transfered from file */
    else if (result.count("file"))
    {
        data = GetDataFile(result, size);
        if (!data)
            return;
    }
    else
    {
        std::cout << "Error: DFU download failed, missing data options\n";
        return;
    }

    if (!data)
    {
        if (dfu_device->DfuDownloadZero(wBlockNum))
        {
            std::cout << "Error: DFU download failed\n";
            return;
        }
    }
    else
    {
        /* send data */
        if (dfu_device->DfuDownload(wBlockNum, data, size))
        {
            std::cout << "Error: DFU download failed\n";
            delete[] data;
            return;
        }
    }

    std::cout << "Info: DFU download Done\n";

    /* check data display */
    if (result.count("display8"))
        this->usb_device->DisplayData8(data, size);
    else if (result.count("display16"))
        this->usb_device->DisplayData16(data, size);
    else if (result.count("display32"))
            this->usb_device->DisplayData32(data, size);
    else if (result.count("display64"))
        this->usb_device->DisplayData64(data, size);

    delete[] data;
}


void USBTestCli::DFU11Upload(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_upload"))
        return;
    std::cout << "\n";
    std::cout << "Info: DFU upload:\n";

    uint16_t wBlockNum = 0;
    if (!result.count("wBlockNum"))
    {
        std::cout << "Warning: Missing --wBlockNum option, assuming wBlockNum is 0\n";
    }
    else
    {
        wBlockNum = result["wBlockNum"].as<uint16_t>();
    }

    /* check the size for device to host transfer */
    if (!result.count("size"))
    {
        std::cout << "Error: Missing --size option\n";
        return;
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    size = result["size"].as<size_t>();
    if (!size)
    {
        std::cout << "Error: DFU upload failed, --size can not be zero\n" ;
        return;
    }
    data = new(std::nothrow) uint8_t[size];
    if (!data)
    {
        std::cout << "Error: DFU upload, Memory allocation error\n" ;
        return ;
    }
    std::memset(data, 0x00, size);

    if (dfu_device->DfuUpload(wBlockNum, data, size))
    {
        std::cout << "Error: DFU download failed\n";
        delete[] data;
        return;
    }

    std::cout << "Info: DFU upload Done\n";

    /* write to the file */
    if (result.count("file"))
    {
        std::string file_name = result["file"].as<std::string>();
        WriteBinFile(file_name, data, size);
    }

    /* check data display */
    if (result.count("display8"))
        this->usb_device->DisplayData8(data, size);
    else if (result.count("display16"))
        this->usb_device->DisplayData16(data, size);
    else if (result.count("display32"))
            this->usb_device->DisplayData32(data, size);
    else if (result.count("display64"))
        this->usb_device->DisplayData64(data, size);

    delete[] data;
}
