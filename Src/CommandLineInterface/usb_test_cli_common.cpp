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

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


extern std::string version;


/* ********************************************************************************************** */
/* ***************************************** CLI Parser ***************************************** */
/* ********************************************************************************************** */


/**
 * @brief USBTestCli::InitApplicationCommands
 * Define the DFUtest Suite general and common CLI options
 */
void USBTestCli::InitApplicationCommands()
{
    options->add_options("Program General Options")
            ("help", "Print help")
            ("show_w", "Display CopyRights Warranty")
            ("show_c", "Display CopyRights")
            ("version", "Display USBTest Suite version")
            ("exit", "Exit application");
}


/**
 * @brief USBTestCli::ParseCommonCmds
 * try to match the Program General Options defined in
 * InitApplicationCommands, and than proceed to execute
 * them
 * @param result cxxopts::ParseResult
 */
void USBTestCli::ParseCommonCmds(const cxxopts::ParseResult &result)
{
    if(result.count("show_w"))
        DisplayWarranty();

    if (result.count("show_c"))
        DisplayCopyRights();

    if (result.count("help"))
        DisplayHelp();

    if (result.count("version"))
    {
        std::cout << "\n";
        std::cout << "Info: USBTest Suite version " << version << "\n";
    }
}


/**
 * @brief USBTestCli::DisplayGenralHelp
 * Display DFUtest Suite general and common CLI options
 */
void USBTestCli::DisplayGenralHelp()
{
    std::cout << "Common options" << std::endl;
    std::cout << "\t-h, --help                  Print help Menu\n";
    std::cout << "\t    --show_w                Display CopyRights Warranty\n";
    std::cout << "\t    --show_c                Display CopyRights\n";
    std::cout << "\t    --version               Display USBTest Suite version\n";
    std::cout << "\t    --exit                  Exit application\n";
    std::cout << "\n";
}


/**
 * @brief USBTestCli::WriteBinFile
 * Write data in the target file in binary format
 * @param file file path
 * @param data input data
 * @param size input data length
 * @return 0 on success, -1 otherwise
 */
int8_t USBTestCli::WriteBinFile(std::string file, uint8_t *data, size_t size)
{
    FILE *f_des = std::fopen(file.c_str(), "wb");
    if (!f_des)
    {
        std::cout << "Error: Unable to open target file: " << file << "\n";
        return -1;
    }

    size_t len = std::fwrite(data, 1, size, f_des);
    if (len != size)
    {
        std::cout << "Error: Unable to write in target file: " << file << "\n";
        std::fclose(f_des);
        return -1;
    }

    std::fclose(f_des);
    std::cout << "Info: Writing in target file: " << file << " Done\n";
    return 0;
}


/**
 * @brief USBTestCli::ReadBinFile
 * Read data from file in binary format. on success the output parameter 'size' will be poppulated
 * with the datta length.
 * @param file file path
 * @param size data length
 * @return a pointer to the read data on success, nullptr otherwise
 */
uint8_t *USBTestCli::ReadBinFile(std::string file, size_t &size)
{
    FILE *f_des = std::fopen(file.c_str(), "rb");
    if (!f_des)
    {
        std::cout << "Error: Unable to open target file: " << file << "\n";
        return nullptr;
    }

    if (std::fseek (f_des, 0, SEEK_END))
    {
        std::cout << "Error: Unable to determin target file: "<< file << " size\n";
        std::fclose(f_des);
        return nullptr;
    }
    long l_size = std::ftell(f_des);
    if (l_size == -1L)
    {
        std::cout << "Error: Unable to determin target file: "<< file << " size\n";
        std::fclose(f_des);
        return nullptr;
    }
    std::rewind(f_des);
    size = static_cast<size_t>(l_size);

    uint8_t *data = new(std::nothrow) uint8_t[size];
    if (!data)
    {
        std::cout << "Error: Unable to read target file: "<< file << ", memory allocation error\n";
        std::fclose(f_des);
        return nullptr;
    }
    std::memset(data, 0x0, size);

    size_t len = std::fread(data, 1, size, f_des);
    if (len != size)
    {
        std::cout << "Error: Unable to read target file: "<< file << "\n";
        delete[] data;
        std::fclose(f_des);
        return nullptr;
    }

    std::fclose(f_des);
    return data;
}



/**
 * @brief USBTestCli::DisplayHelp
 * Display the help menu
 */
void USBTestCli::DisplayHelp()
{
    std::cout << "\n";
    std::cout << "Usage:\n";
    std::cout << "\t[[OPTION <ARGUMENT>] [OPTION <ARGUMENT>] [OPTION <ARGUMENT>] ...]\n\n";

    DisplayGenralHelp();

#if defined (STANDARD_USB)
    DisplayUSBHelp();
#endif

#if defined (USB_IN_DFU_MODE) || defined (DFU_ST_EXTENSION)
    std::cout << "DFU1.1 options" << std::endl;
    std::cout << "\t    --set_altsetting        USB Set Interface Alt Settings"                         << std::endl;
    std::cout << "\t                            exp: --set_altsetting 0x2"                              << std::endl;
    std::cout << "\t    --displaydesc           Display DFU device set of descriptors"                  << std::endl;
    std::cout << "\t    --wBlockNum             initial BlockNumber used for download/upload operations"<< std::endl;
    std::cout << "\t    --detach                Send DFU detach request"                                << std::endl;
    std::cout << "\t    --getstatus             Send a DFU get status request and display result"       << std::endl;
    std::cout << "\t    --clearstatus           Send DFU clear status request"                          << std::endl;
    std::cout << "\t    --getstate              Send DFU get state request and display result"          << std::endl;
    std::cout << "\t    --abort                 Send DFU abort request"                                 << std::endl;
    std::cout << "\t    --dnload0               Send DFU download zero sise request"                    << std::endl;
    std::cout << "\t                            exp: --dnload0 --wBlockNum 0x2"                         << std::endl;
    std::cout << "\t    --dnload8               Send DFU download request with length = 1 Byte"         << std::endl;
    std::cout << "\t                            exp: --dnload8 0xAA --wBlockNum 0x2"                    << std::endl;
    std::cout << "\t    --dnload16              Send DFU download request with length = 2 Bytes"        << std::endl;
    std::cout << "\t                            exp: --dnload16 0xBBAA --wBlockNum 0x2"                 << std::endl;
    std::cout << "\t    --dnload32              Send DFU download request with length = 4 Bytes"        << std::endl;
    std::cout << "\t                            exp: --dnload32 0xFF00BBAA --wBlockNum 0x2"             << std::endl;
    std::cout << "\t    --dnload64              Send DFU download request with length = 8 Bytes"        << std::endl;
    std::cout << "\t                            exp: --dnload32 0xDE004522FF00BBAA --wBlockNum 0x2"     << std::endl;
    std::cout << "\t    --upload8               Send DFU upload request with the specified length"      << std::endl;
    std::cout << "\t                            (bytes nbr) and display the result as Bytes"            << std::endl;
    std::cout << "\t                            exp: --upload8 0x7000 --wBlockNum 0x2"                  << std::endl;
    std::cout << "\t    --upload16              Send DFU upload request with the specified length"      << std::endl;
    std::cout << "\t                            (half words nbr) and display the result as HalfWords"   << std::endl;
    std::cout << "\t                            exp: --upload16 0x3800 --wBlockNum 0x2"                 << std::endl;
    std::cout << "\t    --upload32              Send DFU upload request with the specified length"      << std::endl;
    std::cout << "\t                            (words nbr) and display the result as Words"            << std::endl;
    std::cout << "\t                            exp: --upload32 0x1C00 --wBlockNum 0x2"                 << std::endl;
    std::cout << "\t    --upload64              Send DFU DFU upload request with the specified length"  << std::endl;
    std::cout << "\t                            (doublewords nbr) and display the result as DoubleWords"<< std::endl;
    std::cout << "\t                            exp: --upload64 0xE00 --wBlockNum 0x2"                  << std::endl;
    std::cout << "\t    --dnload_file           Send DFU download requests with data taken from file"   << std::endl;
    std::cout << "\t                            exp: --dnload_file --wBlockNum 0x2 -file ./test_dfu.bin"<< std::endl;
    std::cout << "\t    --upload_file           Send DFU upload request with the specified length"      << std::endl;
    std::cout << "\t                            (bytes nbr) and store result in the target file"        << std::endl;
    std::cout << "\t                            exp: --upload_file 0x7000 --wBlockNum 2 -file ./a.bin"  << std::endl;
    std::cout << std::endl;
#endif

#if defined (DFU_ST_EXTENSION)
    std::cout << "DFU1.1 St-Extension options" << std::endl;
    std::cout << "\t    --se_displayinter       DFU St-Ex Display Interfaces"                           << std::endl;
    std::cout << "\t    --se_get                Send DFU St-Ex Get Command request"                     << std::endl;
    std::cout << "\t    --se_setadd             Send DFU St-Ex Set Address Pointer"                     << std::endl;
    std::cout << "\t                            exp: --se_setadd 0x8000000"                             << std::endl;
    std::cout << "\t    --se_erase              Send DFU St-Ex Erase Sector request"                    << std::endl;
    std::cout << "\t                            exp: --se_erase 0x8"                                    << std::endl;
    std::cout << "\t    --se_eraseall           Send DFU St-Ex Mass Erase request"                      << std::endl;
    std::cout << "\t    --se_readunp            Send DFU St-Ex Read Unprotect request"                  << std::endl;
    std::cout << "\t    --se_leavedfu           Send DFU St-Ex Leave DFU Mode request"                  << std::endl;
    std::cout << "\t                            exp: --se_leavedfu 0x8000000"                           << std::endl;
    std::cout << "\t    --se_dnload8            Send DFU St-Ex download request with length = 1 Byte"   << std::endl;
    std::cout << "\t                            exp: --se_dnload8 0x80"                                 << std::endl;
    std::cout << "\t    --se_dnload16           Send DFU St-Ex download request with length = 2 Bytes"  << std::endl;
    std::cout << "\t                            exp: --se_dnload16 0xD580"                              << std::endl;
    std::cout << "\t    --se_dnload32           Send DFU St-Ex download request with length = 4 Bytes"  << std::endl;
    std::cout << "\t                            exp: --se_dnload32 0xFF88D580"                          << std::endl;
    std::cout << "\t    --se_dnload64           Send DFU St-Ex download request with length = 8 Bytes"  << std::endl;
    std::cout << "\t                            exp: --se_dnload64 0xF0000000FF88D580"                  << std::endl;
    std::cout << "\t    --se_upload8            Send DFU St-Ex upload request with the specified length"<< std::endl;
    std::cout << "\t                            (bytes nbr) and display the results as Bytes"           << std::endl;
    std::cout << "\t                            exp: --se_upload8 0x7000"                               << std::endl;
    std::cout << "\t    --se_upload16           Send DFU St-Ex upload request with the specified length"<< std::endl;
    std::cout << "\t                            (halfwords nbr) and display the results as Half Words"  << std::endl;
    std::cout << "\t                            exp: --se_upload16 0x3800"                              << std::endl;
    std::cout << "\t    --se_upload32           Send DFU St-Ex upload request with the specified length"<< std::endl;
    std::cout << "\t                            (words nbr) and display the results as Words"           << std::endl;
    std::cout << "\t                            exp: --se_upload32 0x1C00"                              << std::endl;
    std::cout << "\t    --se_upload64           Send DFU St-Ex upload request with the specified length"<< std::endl;
    std::cout << "\t                            (doublewords nbr) and display the result as DoubleWords"<< std::endl;
    std::cout << "\t                            exp: --se_upload64 0xE00"                               << std::endl;
    std::cout << "\t    --se_dnload_file        Send DFU St-Ex download requests with data from file"   << std::endl;
    std::cout << "\t                            exp: --se_dnload_file -file ./test_dfu.bin"             << std::endl;
    std::cout << "\t    --se_upload_file        Send DFU St-Ex upload request with the specified length"<< std::endl;
    std::cout << "\t                            (bytes nbr) and store result in the target file"        << std::endl;
    std::cout << "\t                            exp: --se_upload_file 0x7000 -file ./a.bin"             << std::endl;
    std::cout << std::endl;
#endif
}
