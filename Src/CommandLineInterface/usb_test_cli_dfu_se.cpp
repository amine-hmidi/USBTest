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

void USBTestCli::InitDFUSECommands()
{
    options->add_options("DFUSE Options")
            ("dfuse", "Connect as a USB in DFU mode with st extension")
            ("dfuse_get", "Send a DFUSE get command request")
            ("dfuse_setaddress", "Send a DFUSE set address pointer request")
            ("dfuse_erase", "Send a DFUSE sector erase request")
            ("dfuse_masserase", "Send a DFUSE mass erase request")
            ("dfuse_readunp", "Send a DFUSE read unprotect request")
            ;
}


void USBTestCli::DisplayDFUSEHelp()
{
    std::stringstream stream;

    stream << "DFUSE options\n";
    /* **** */
    stream << "\t    --dfuse                 Connect as USB in DFU mode with St extension\n";
    stream << "\t    --dfuse_get             Send a DFUSE get command request\n";
    stream << "\t    --dfuse_setaddress      Send a DFUSE set address pointer request\n";
    stream << "\t    --dfuse_erase           Send a DFUSE sector erase request\n";
    stream << "\t    --dfuse_masserase       Send a DFUSE mass erase request\n";
    stream << "\t    --dfuse_readunp         Send a DFUSE read unprotect request\n";

    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
}


void USBTestCli::ParseDFUSECmds(const cxxopts::ParseResult &result)
{
    if(result.count("dfuse"))
    {
        /* init the dfu device objects */
        ConnectDFUSE();
    }

    if (!this->usb_device)
        return;

    if (this->usb_device->DeviceClass() != StandardUSB::USBClassType::DFU_ST_EX)
        return;

    DFUSE *dfu_se = dynamic_cast<DFUSE *>(usb_device);

    DFUSEGetCommand(result, dfu_se);
    DFUSESetAddressPointer(result, dfu_se);
    DFUSEErase(result, dfu_se);
    DFUSEMassErase(result, dfu_se);
    DFUSEReadUnprotect(result, dfu_se);
}


void USBTestCli::ConnectDFUSE()
{
    /* init the usb device objects */
    if (usb_device)
    {
        delete usb_device;
        usb_device = nullptr;
    }

    usb_device = new(std::nothrow) DFUSE();
    if (!usb_device)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to initialize the usb device, Mmeory allocation error");
        return;
    }

    /* open the usb device */
    DFUClass *dfu_device = dynamic_cast<DFUSE *>(usb_device);
    if (dfu_device->OpenDevice())
    {
        delete usb_device;
        usb_device = nullptr;
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,"Connection established");
}


void USBTestCli::DFUSEGetCommand(const cxxopts::ParseResult &result, DFUSE *dfu_se)
{
    if (!result.count("dfuse_get"))
        return;

    uint8_t data[4] = {0x00};
    if (dfu_se->DfuseGetCommand(data, 4))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "DFUSE get command done");

    /* check data display */
    if (result.count("display16"))
        cli_dm->DisplayData16(data, 4);
    else if (result.count("display32"))
        cli_dm->DisplayData32(data, 4);
    else if (result.count("display64"))
        cli_dm->DisplayData64(data, 4);
    else
        cli_dm->DisplayData8(data, 4);
}


void USBTestCli::DFUSESetAddressPointer(const cxxopts::ParseResult &result, DFUSE *dfu_se)
{
    if (!result.count("dfuse_setaddress"))
        return;

    if (!result.count("address"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --address option");
    }
    uint32_t address = result["address"].as<uint32_t>();

    if (dfu_se->DfuSeSetAddress(address))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "DFUSE set address pointer done");
}


void USBTestCli::DFUSEErase(const cxxopts::ParseResult &result, DFUSE *dfu_se)
{
    if (!result.count("dfuse_erase"))
        return;

    if (!result.count("address"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --address option");
    }
    uint32_t address = result["address"].as<uint32_t>();

    if (dfu_se->DfuSeEraseSector(address))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "DFUSE sector erase done");
}


void USBTestCli::DFUSEMassErase(const cxxopts::ParseResult &result, DFUSE *dfu_se)
{
    if (!result.count("dfuse_masserase"))
        return;

    if (dfu_se->DfuSeMassErase())
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "DFUSE mass erase done");
}


void USBTestCli::DFUSEReadUnprotect(const cxxopts::ParseResult &result, DFUSE *dfu_se)
{
    if (!result.count("dfuse_readunp"))
        return;

    if (dfu_se->DfuSeReadUnprotect())
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "DFUSE read unprotect done");
}
