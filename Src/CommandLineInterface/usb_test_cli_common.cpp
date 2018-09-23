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
}
