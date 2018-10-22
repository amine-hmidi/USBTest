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
        cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                             "USBTest Suite version " + version);
    }
}


/**
 * @brief USBTestCli::DisplayGenralHelp
 * Display DFUtest Suite general and common CLI options
 */
void USBTestCli::DisplayGenralHelp()
{
    std::stringstream stream;
    stream << "Common options\n";
    stream << "\t-h, --help                  Print help Menu\n";
    stream << "\t    --show_w                Display CopyRights Warranty\n";
    stream << "\t    --show_c                Display CopyRights\n";
    stream << "\t    --version               Display USBTest Suite version\n";
    stream << "\t    --exit                  Exit application";
    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
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
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to open target file: " + file);
        return -1;
    }

    size_t len = std::fwrite(data, 1, size, f_des);
    if (len != size)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to write in target file: " + file);
        std::fclose(f_des);
        return -1;
    }

    std::fclose(f_des);
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "Writing in target file: " + file + " Done");
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
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to open target file: " + file);
        return nullptr;
    }

    if (std::fseek (f_des, 0, SEEK_END))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to determin target file: " + file + " size");
        std::fclose(f_des);
        return nullptr;
    }
    long l_size = std::ftell(f_des);
    if (l_size == -1L)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to determin target file: " + file + " size");
        std::fclose(f_des);
        return nullptr;
    }
    std::rewind(f_des);
    size = static_cast<size_t>(l_size);

    uint8_t *data = new(std::nothrow) uint8_t[size];
    if (!data)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to read target file: " + file + ", memory allocation error");
        std::fclose(f_des);
        return nullptr;
    }
    std::memset(data, 0x0, size);

    size_t len = std::fread(data, 1, size, f_des);
    if (len != size)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to read target file: " + file);
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
    std::stringstream stream;
    stream << "Usage:\n";
    stream << "\t[[OPTION <ARGUMENT>] [OPTION <ARGUMENT>] [OPTION <ARGUMENT>] ...]\n\n";
    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());

    DisplayGenralHelp();
#if defined (STANDARD_USB)
    DisplayUSBHelp();
#endif
#if defined(USB_IN_DFU_MODE)
    DisplayDFU11Help();
#endif
}
