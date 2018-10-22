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
            ("dfu_dnload0", "Send a DFU download request with zero length")
            ("dfu_upload", "Send a DFU upload request")
            ("wBlockNum", "The packet number from which the download/upload will start",\
             cxxopts::value<uint16_t>())
            ;
}


void USBTestCli::DisplayDFU11Help()
{
    std::stringstream stream;

    stream << "DFU 1.1 options\n";
    /* **** */
    stream << "\t    --dfu                   Connect as USB in DFU mode (must use --idvendor\n";
    stream << "\t                            and --idproduct usb options) \n";
    stream << "\t    --dfu_getstatus         Request the DFU device status\n";
    stream << "\t    --dfu_getstate          Request the DFU device state\n";
    stream << "\t    --dfu_clearstatus       Send a DFU device clear status request\n";
    stream << "\t    --dfu_abort             Send a DFU device abort request\n";
    stream << "\t    --dfu_detach            Send a DFU device detach request\n";
    stream << "\t    --dfu_dnload            Send a DFU download request\n";
    stream << "\t    --dfu_dnload0           Send a DFU download request with zero length\n";
    stream << "\t    --dfu_upload            Send a DFU upload request\n";
    stream << "\t    --wBlockNum             The packet number from which the download/upload\n";
    stream << "\t                            operation will start";

    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
}


void USBTestCli::ParseDFU11Cmds(const cxxopts::ParseResult &result)
{
    if(result.count("dfu"))
    {
        /* Check if both idvendor and idproduct are present */
        if(!result.count("idvendor"))
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "Missing --idvendor option");
            return;
        }

        if(!result.count("idproduct"))
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "Missing --idproduct option");
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
    DFU11Upload(result, dfu_device);
    DFU11Download(result, dfu_device);
    DFU11DownloadZero(result, dfu_device);
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
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to initialize the usb device, Mmeory allocation error");
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

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,"Connection established");
}


void USBTestCli::DFU11GetStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_getstatus"))
        return;

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

    DFUClass::DFUState state = dfu_device->DfuGetState();
    if (state == DFUClass::DFUState::stateUNKNOWN)
        return;

    dfu_device->DisplayDfuState();
}


void USBTestCli::DFU11ClearStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_clearstatus"))
        return;

    if (dfu_device->DfuClearStatus())
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "DFU clear status Done");
}


void USBTestCli::DFU11Abort(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_abort"))
        return;

    if (dfu_device->DfuAbort())
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "DFU abort Done");
}


void USBTestCli::DFU11Detach(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_detach"))
        return;

    if (dfu_device->DfuDetach())
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "DFU detach Done");
}


void USBTestCli::DFU11Download(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_dnload"))
        return;

    uint16_t wBlockNum = 0;
    if (!result.count("wBlockNum"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Missing --wBlockNum option, assuming wBlockNum is 0");
    }
    else
    {
        wBlockNum = result["wBlockNum"].as<uint16_t>();
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    if (result.count("data0"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Rejected --data0 option, consider using dfu_dnload0 option");
        return;
    }

    /* 1, 2, 4 or 8 bytes pointer data
     * ignore --file, check --size options if any
     */
    else if(result.count("data8") || result.count("data16") || result.count("data32") ||\
            result.count("data64"))
    {
        data = GetDataCli(result, size);
        if (!data)
            return;
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
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --data8(16/32/64) or --file options");
        return;
    }

    /* send data */
    if (dfu_device->DfuDownload(wBlockNum, data, size))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "DFU download failed");
        delete[] data;
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,"DFU download Done");

    /* check data display */
    if (result.count("display8"))
        cli_dm->DisplayData8(data, size);
    else if (result.count("display16"))
        cli_dm->DisplayData16(data, size);
    else if (result.count("display32"))
        cli_dm->DisplayData32(data, size);
    else if (result.count("display64"))
        cli_dm->DisplayData64(data, size);

    delete[] data;
}


void USBTestCli::DFU11DownloadZero(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_dnload0"))
        return;

    uint16_t wBlockNum = 0;
    if (!result.count("wBlockNum"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Missing --wBlockNum option, assuming wBlockNum is 0");
    }
    else
    {
        wBlockNum = result["wBlockNum"].as<uint16_t>();
    }

    /* send data */
    if (dfu_device->DfuDownloadZero(wBlockNum))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "DFU download 0 failed");
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,"DFU download 0 Done");
}


void USBTestCli::DFU11Upload(const cxxopts::ParseResult &result, DFUClass *dfu_device)
{
    if (!result.count("dfu_upload"))
        return;

    uint16_t wBlockNum = 0;
    if (!result.count("wBlockNum"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Missing --wBlockNum option, assuming wBlockNum is 0");
    }
    else
    {
        wBlockNum = result["wBlockNum"].as<uint16_t>();
    }

    /* check the size for device to host transfer */
    if (!result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,"Missing --size option");
        return;
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    size = result["size"].as<size_t>();
    if (!size)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU upload failed, --size can not be zero");
        return;
    }
    data = new(std::nothrow) uint8_t[size];
    if (!data)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "DFU upload, Memory allocation error");
        return ;
    }
    std::memset(data, 0x00, size);

    if (dfu_device->DfuUpload(wBlockNum, data, size))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "DFU upload failed");
        delete[] data;
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "DFU upload Done");

    /* write to the file */
    if (result.count("file"))
    {
        std::string file_name = result["file"].as<std::string>();
        WriteBinFile(file_name, data, size);
    }

    /* check data display */
    if (result.count("display8"))
        cli_dm->DisplayData8(data, size);
    else if (result.count("display16"))
        cli_dm->DisplayData16(data, size);
    else if (result.count("display32"))
        cli_dm->DisplayData32(data, size);
    else if (result.count("display64"))
        cli_dm->DisplayData64(data, size);

    delete[] data;
}
