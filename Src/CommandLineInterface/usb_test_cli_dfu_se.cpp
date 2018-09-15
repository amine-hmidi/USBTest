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

#if defined (DFU_ST_EXTENSION)

/* C++ Includes */
#include <iostream>
#include <string>

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


/* **************************************************************************************************** */
/* ******************************************** CLI Parser ******************************************** */
/* **************************************************************************************************** */


void USBTestCli::InitDFUSeCommands()
{
    options->add_options("DFU1.1 St-Extension")
            ("se_displayinter", "DFUSE Get")
            ("se_get", "DFUSE Get")
            ("se_setadd", "DFUSE Set Address Pointer" ,\
             cxxopts::value<uint32_t>())
            ("se_erase", "DFUSE Erase Sectors" ,\
             cxxopts::value<std::vector<uint32_t>>())
            ("se_eraseall", "DFUSE Mass Erase")
            ("se_readunp", "DFUSE Read Unprotect")
            ("se_leavedfu", "DFUSE Leave DFU mode")
            ("se_dnload8", "DFU Download 1 Byte" ,\
             cxxopts::value<uint8_t>())
            ("se_dnload16", "DFUSE Download 2 Byte" ,\
             cxxopts::value<uint16_t>())
            ("se_dnload32", "DFUSE Download 4 Byte" ,\
             cxxopts::value<uint32_t>())
            ("se_dnload64", "DFUSE Download 8 Byte" ,\
             cxxopts::value<uint64_t>())
            ("se_dnload_file", "DFUSE Download File")
            ("se_upload8", "DFUSE Upload 1 Byte" ,\
             cxxopts::value<uint32_t>())
            ("se_upload16", "DFUSE Upload 2 Byte" ,\
             cxxopts::value<uint32_t>())
            ("se_upload32", "DFUSE Upload 4 Byte" ,\
             cxxopts::value<uint32_t>())
            ("se_upload64", "DFUSE Upload 8 Byte" ,\
             cxxopts::value<uint32_t>())
            ("se_upload_file", "DFUSE Upload File" ,\
             cxxopts::value<uint32_t>());
}


void USBTestCli::ParseDfuSeCmds(const cxxopts::ParseResult &result)
{
    if ((!this->usb_device) || (this->usb_device->DeviceClass() != StandardUSB::USBClassType::DFU_ST_EX))
        return;

    DFUStExtension *se_dfu = dynamic_cast<DFUStExtension *>(this->usb_device);

    DFUSeDisplayInterfaces(se_dfu, result);
    DFUSeGetCommand(se_dfu, result);
    DFUSeSetAddresspointer(se_dfu, result);
    DFUSeMassErase(se_dfu, result);
    DFUSeSectorErase(se_dfu, result);
    DFUSeReadUnprotect(se_dfu, result);
    DFUSeLeaveDfuMode(se_dfu, result);
    DFUSeDnload1Byte(se_dfu, result);
    DFUSeDnload2Bytes(se_dfu, result);
    DFUSeDnload4Bytes(se_dfu, result);
    DFUSeDnload8Bytes(se_dfu, result);
    DFUSeUploadDisplay1Byte(se_dfu, result);
    DFUSeUploadDisplay2Bytes(se_dfu, result);
    DFUSeUploadDisplay4Bytes(se_dfu, result);
    DFUSeUploadDisplay8Bytes(se_dfu, result);
    DFUSeDnloadFile(se_dfu, result);
    DFUSeUploadFile(se_dfu, result);
}


void USBTestCli::DFUSeSetAddresspointer(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    if (result.count("se_setadd"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Set Address Pointer:" << std::endl;

        uint32_t address = result["se_setadd"].as<uint32_t>();
        if (se_dfu->SetAddressPointer(address))
            return;

        std::cout << "Info: DFU St-Extension Set Address Pointer Done" << std::endl;
    }
}


void USBTestCli::DFUSeDisplayInterfaces(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    if (result.count("se_displayinter"))
        se_dfu->DisplayInterfaces();
}


void USBTestCli::DFUSeGetCommand(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    if (result.count("se_get"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Get Command:" << std::endl;

        if (se_dfu->GetCommand())
            return;

        std::cout << "Info: DFU St-Extension Get Command Done" << std::endl;
    }
}


void USBTestCli::DFUSeMassErase(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Mass Erase */
    if (result.count("se_eraseall"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Mass Erase:" << std::endl;

        if (se_dfu->MassErase())
            return;

        std::cout << "Info: DFU St-Extension Mass Erase Done" << std::endl;
    }
}


void USBTestCli::DFUSeSectorErase(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension erase sectors */
    if (result.count("se_erase"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Sector Erase:" << std::endl;

        std::vector<uint32_t> sectors = result["se_erase"].as<std::vector<uint32_t>>();
        for (const uint32_t &index : sectors)
        {
            uint32_t address = se_dfu->GetSectorAddress(index);
            if (address == 0xFFFFFFFE)
            {
                std::cout << "Error: Unable to extract Flash memory information from interface string descriptor" << std::endl;
                return;
            }
            if (address == 0xFFFFFFFF)
            {
                std::cout << "Warning: Index: " << index << " is greater than the number of flash memory sectors,"\
                                                            " command will not be sent" << std::endl;
                continue;
            }
            if (address == 0xFFFFFFFD)
            {
                std::cout << "Warning: Sector Index: " << index << " is not Erasable, command will not be sent" << std::endl;
                continue;
            }

            if (se_dfu->EraseSector(address))
                std::cout << "Error: Failed to erase sector: " << index << " @address: 0x" << \
                             std::hex << std::setfill ('0') << std::setw(4) << address << std::endl;
            else
                std::cout << "Info: erase sector: " << index << " @address: 0x" << std::hex << \
                             std::setfill ('0') << std::setw(4) << address << " Done" << std::endl;
        }
    }
}


void USBTestCli::DFUSeReadUnprotect(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Read Unprotect */
    if (result.count("se_readunp"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Read Unprotect:" << std::endl;

        if(se_dfu->ReadUnprotect())
            return;

        std::cout << "Info: DFU St-Extension Read Unprotect Done" << std::endl;
    }
}


void USBTestCli::DFUSeLeaveDfuMode(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Leave DFU  */
    if (result.count("se_leavedfu"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Leave DFU:" << std::endl;

        if (se_dfu->LeaveDfuMode())
            return;

        std::cout << "Info: DFU St-Extension Leave DFU Done" << std::endl;
    }
}


void USBTestCli::DFUSeDnload1Byte(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Dnload 1bytes */
    if (result.count("se_dnload8 "))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Dnload 1bytes:" << std::endl;

        uint8_t data = result["se_dnload8"].as<uint8_t>();

        if(se_dfu->DfuSeDownloadData(&data, 0x01))
            return;

        std::cout << "DFU St-Extension Dnload 1bytes Done" << std::endl;
    }
}


void USBTestCli::DFUSeDnload2Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Dnload 2bytes */
    if (result.count("se_dnload16"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Dnload 2bytes:" << std::endl;

        uint16_t value = result["se_dnload16"].as<uint16_t>();
        uint8_t data[2] = {static_cast<uint8_t>(static_cast<uint32_t>(value) & 0xFF),
                           static_cast<uint8_t>((static_cast<uint32_t>(value) >> 8 ) & 0xFF)};

        if(se_dfu->DfuSeDownloadData(data, 0x02))
            return;

        std::cout << "DFU St-Extension Dnload 2bytes Done" << std::endl;
    }
}


void USBTestCli::DFUSeDnload4Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Dnload 4 bytes */
    if (result.count("se_dnload32"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Dnload 4 bytes:" << std::endl;

        uint32_t value = result["se_dnload32"].as<uint32_t>();
        uint8_t data[4] = {static_cast<uint8_t>(value & 0xFF),
                           static_cast<uint8_t>((value >> 8 ) & 0xFF),
                           static_cast<uint8_t>((value >> 16 ) & 0xFF),
                           static_cast<uint8_t>((value >> 24 ) & 0xFF)};

        if(se_dfu->DfuSeDownloadData(data, 0x04))
            return;

        std::cout << "DFU St-Extension Dnload 4 bytes Done" << std::endl;
    }
}


void USBTestCli::DFUSeDnload8Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Dnload 8 bytes */
    if (result.count("se_dnload64"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Dnload 8 bytes:" << std::endl;

        uint64_t value = result["se_dnload64"].as<uint64_t>();
        uint8_t data[8] = {static_cast<uint8_t>(value & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 8 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 16 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 24 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 32 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 40 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 48 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 56 ) & 0xFF)};

        if(se_dfu->DfuSeDownloadData(data, 0x08))
            return;

        std::cout << "DFU St-Extension Dnload 8 bytes Done" << std::endl;
    }
}


void USBTestCli::DFUSeUploadDisplay1Byte(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Upload in 1 Byte */
    if (result.count("se_upload8"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Upload and Display as 1 Byte:" << std::endl;

        /* get the number of bytes */
        uint32_t size = result["se_upload8"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            std::cout << "Error: Unable to send se_upload8, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, size);

        /*upload data from device */
        if (se_dfu->DfuSeUploadData(data, size))
            return;

        se_dfu->DisplayData8(data, size);
        delete[] data;
    }
}


void USBTestCli::DFUSeUploadDisplay2Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Upload in 2 Byte */
    if (result.count("se_upload16"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Upload and Display as 2 Bytes:" << std::endl;

        /* get the number of bytes */
        uint32_t size = result["se_upload16"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[2 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send se_upload16, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 2 * size);

        /*upload data from device */
        if (se_dfu->DfuSeUploadData(data, 2 * size))
            return;

        se_dfu->DisplayData16(data, 2 * size);
        delete[] data;
    }
}


void USBTestCli::DFUSeUploadDisplay4Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Upload in 4 Byte */
    if (result.count("se_upload32"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Upload and Display as 4 Bytes:" << std::endl;

        /* get the number of bytes */
        uint32_t size = result["se_upload32"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[4 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send se_upload32, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 4 * size);

        /*upload data from device */
        if (se_dfu->DfuSeUploadData(data, 4 * size))
            return;

        se_dfu->DisplayData32(data, 4 * size);
        delete[] data;
    }
}


void USBTestCli::DFUSeUploadDisplay8Bytes(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Upload in 8 Byte */
    if (result.count("se_upload64"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Upload and Display as 8 Bytes:" << std::endl;

        /* get the number of bytes */
        uint32_t size = result["se_upload64"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[8 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send se_upload64, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 8 * size);

        /*upload data from device */
        if (se_dfu->DfuSeUploadData(data, 8 * size))
            return;

        se_dfu->DisplayData64(data, 8 * size);
        delete[] data;
    }
}


void USBTestCli::DFUSeDnloadFile(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Donwload file */
    if (result.count("se_dnload_file"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Donwload file:" << std::endl;

        if (!result.count("file"))
        {
            std::cout << "Error: Missing --file option, please specify the target file" << std::endl;
            return;
        }

        /* get the file name */
        std::string file_name = result["file"].as<std::string>();

        /* open file */
        FILE *file = fopen(file_name.c_str(), "rb");
        if(!file)
        {
            std::cout << "Error: Unable to open target file: "<< file_name << std::endl;
            return;
        }

        /* obtain file size */
        if (fseek (file , 0 , SEEK_END))
        {
            std::cout << "Error: Unable to determin target file: "<< file_name << " size" << std::endl;
            fclose(file);
            return;
        }
        long lSize = ftell (file);
        if (lSize == -1L)
        {
            std::cout << "Error: Unable to determin target file: "<< file_name << " size" << std::endl;
            fclose(file);
            return;
        }
        rewind (file);

        /* allocate memory */
        char *data = new(std::nothrow) char[lSize];
        if (!data)
        {
            std::cout << "Error: Unable to Allocate Memory before Donwloading file: "<< file_name << std::endl;
            fclose(file);
            return;
        }
        memset(data, 0x00, static_cast<size_t>(lSize));

        /* read the file */
        size_t  re_result = fread (data, 1, static_cast<size_t>(lSize), file);
        if (re_result != static_cast<uint64_t>(lSize))
        {
            std::cout << "Error: Unable to read data from file before Donwloading, file: "<< file_name << std::endl;
            fclose(file);
            delete[] data;
            return;
        }

        /* Send Data */
        if (se_dfu->DfuSeDownloadData(reinterpret_cast<const uint8_t *>(const_cast<const char *>(data)), static_cast<uint32_t>(lSize)))
        {
            fclose(file);
            delete[] data;
            return;
        }

        std::cout << "Info: DFU St-Extension Donwload file: " << file_name << " Done" << std::endl;
        fclose(file);
        delete[] data;
    }
}


void USBTestCli::DFUSeUploadFile(DFUStExtension *se_dfu, const cxxopts::ParseResult &result)
{
    /* DFU St-Extension Upload file */
    if (result.count("se_upload_file"))
    {
        std::cout << std::endl;
        std::cout << "DFU St-Extension Upload file:" << std::endl;

        if (!result.count("file"))
        {
            std::cout << "Error: Missing --file option, please specify the target file" << std::endl;
            return;
        }

        /* get the file name */
        std::string file_name = result["file"].as<std::string>();

        /* get the number of bytes */
        uint32_t size = result["se_upload_file"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            std::cout << "Error: Unable to send Upload file: " << file_name << " Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, size);

        /*upload data from device */
        if (se_dfu->DfuSeUploadData(data, size))
        {
            delete[] data;
            return;
        }

        /* open file */
        FILE *file = fopen(file_name.c_str(), "wb");
        if(!file)
        {
            std::cout << "Error: Unable to open target file: "<< file_name << std::endl;
            delete[] data;
            return;
        }

        /* Write data */
        size_t w_result = fwrite(data, 1, size, file);
        if (w_result != size)
        {
            std::cout << "Error: Unable to Write to target file: "<< file_name << std::endl;
            fclose(file);
            delete[] data;
            return;
        }

        fclose(file);
        delete[] data;

        std::cout << "Info: DFU St-Extension Upload file: " << file_name << " Done" << std::endl;
    }
}


#endif
