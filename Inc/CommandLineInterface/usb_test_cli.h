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

#ifndef DFU_TEST_CLI_H
#define DFU_TEST_CLI_H

/* C++ Includes */
#include <iostream>
#include <iomanip>
#include <string>
#include <istream>
#include <vector>
#include <cstdlib>

/* C Includes */

/* User Includes */
#include "cxxopts.hpp"
#if defined (STANDARD_USB)
#include "standard_usb.h"
#endif
#if defined (USB_IN_DFU_MODE)
#include "dfu_class.h"
#endif


class USBTestCli
{
public:

    /* ****************************************************************************************** */
    /* ****************************** Class Constructor/Destructor ****************************** */
    /* ****************************************************************************************** */
    USBTestCli(int &, char **&argv);
    ~USBTestCli();
    USBTestCli() = delete;
    USBTestCli (const USBTestCli &) = delete;
    USBTestCli& operator = (const USBTestCli &) = delete;
    USBTestCli (const USBTestCli &&) = delete;
    USBTestCli& operator = (USBTestCli &&) = delete;

    /* ****************************************************************************************** */
    /* ******************************** cli initialization state ******************************** */
    /* ****************************************************************************************** */
    bool IsOk() const { return is_ok; }
    static const std::string Version() {return version;}

    /* ****************************************************************************************** */
    /* *************************** Parsing and executing cli options **************************** */
    /* ****************************************************************************************** */
    int execute();

private:

    /* app version */
    static std::string version;
    /* cli initialization state */
    bool is_ok = false;
    /* application path */
    char *app_path = nullptr;
    /* cxxopts options */
    cxxopts::Options *options = nullptr;
    /* options list */
    char **arguments = nullptr;
    /* options number */
    int argument_nbr = 0x00;
#if defined (STANDARD_USB)
    /* USB Device */
    StandardUSB *usb_device = nullptr;
#endif

    /* ****************************************************************************************** */
    /* *************************************** CLI Parser *************************************** */
    /* ****************************************************************************************** */
    void InitCommands();
    void InitApplicationCommands();
    void ParseCommonCmds(const cxxopts::ParseResult &result);
    void DisplayHelp();
    void DisplayGenralHelp();
    int8_t WriteBinFile(std::string file, uint8_t *data, size_t size);
    uint8_t *ReadBinFile(std::string file, size_t &size);
#if defined (STANDARD_USB)
    void InitUSBCommands();
    void DisplayUSBHelp();
    void ParseUSBCmds(const cxxopts::ParseResult &result);
    void ConnectUSB(uint16_t idVendor = 0xFFFF, uint16_t idProduct = 0xFFFF);
    void DisplayDescriptors(const cxxopts::ParseResult &result);
    void GetDeviceStatus(const cxxopts::ParseResult &result);
    void ClearDeviceFeature(const cxxopts::ParseResult &result);
    void SetDeviceFeature(const cxxopts::ParseResult &result);
    void SetDeviceAddress(const cxxopts::ParseResult &result);
    void GetDeviceDesriptor(const cxxopts::ParseResult &result);
    void SetDeviceDesriptor(const cxxopts::ParseResult &result);
    void GetDeviceConfig(const cxxopts::ParseResult &result);
    void SetDeviceConfig(const cxxopts::ParseResult &result);
    void GetStringDescriptor(const cxxopts::ParseResult &result);
    void GetInterfaceStatus(const cxxopts::ParseResult &result);
    void ClearInterfaceFeature(const cxxopts::ParseResult &result);
    void SetInterfaceFeature(const cxxopts::ParseResult &result);
    void SetInterfaceAltSetting(const cxxopts::ParseResult &result);
    void GetInterfaceAltSetting(const cxxopts::ParseResult &result);
    void GetEndpointStatus(const cxxopts::ParseResult &result);
    void ClearEndpointFeature(const cxxopts::ParseResult &result);
    void SetEndpointFeature(const cxxopts::ParseResult &result);
    void SyncEndpointFrame(const cxxopts::ParseResult &result);
    void ClaimInterface(const cxxopts::ParseResult &result);
    void ReleaseInterface(const cxxopts::ParseResult &result);
    void ResetDevice(const cxxopts::ParseResult &result);
    void ControlTransfer(const cxxopts::ParseResult &result);
    void BulkTransfer(const cxxopts::ParseResult &result);
    void InterruptTransfer(const cxxopts::ParseResult &result);
    uint8_t *GetDataCli(const cxxopts::ParseResult &result, size_t &size);
    uint8_t *GetDataFile(const cxxopts::ParseResult &result, size_t &size);
#endif
#if defined (USB_IN_DFU_MODE)
    void InitDFU11Commands();
    void DisplayDFU11Help();
    void ParseDFU11Cmds(const cxxopts::ParseResult &result);
    void ConnectDFU11(uint16_t idVendor, uint16_t idProduct);
    void DFU11GetStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11GetState(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11ClearStatus(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11Abort(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11Detach(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11Download(const cxxopts::ParseResult &result, DFUClass *dfu_device);
    void DFU11Upload(const cxxopts::ParseResult &result, DFUClass *dfu_device);
#endif




    /* ****************************************************************************************** */
    /* ***************************** Display CopyRights and Warraty ***************************** */
    /* ****************************************************************************************** */
    void DisplayCopyRights();
    void DisplayWarranty();

};

#endif // DFU_TEST_CLI_H
