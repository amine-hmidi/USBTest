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

#if defined (USB_IN_DFU_MODE) || defined (DFU_ST_EXTENSION)

/* C++ Includes */
#include <iostream>
#include <string>

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"


/* **************************************************************************************************** */
/* ******************************************** CLI Parser ******************************************** */
/* **************************************************************************************************** */


void USBTestCli::InitStdDFUCommands()
{
    options->add_options("DFU1.1")
            ("set_altsetting", "USB Set Interface Alt Setting",\
             cxxopts::value<uint8_t>())
            ("displaydesc", "DFU Detach")
            ("detach", "DFU Detach")
            ("getstatus", "DFU GetStatus")
            ("clearstatus", "DFU ClearStatus")
            ("getstate", "DFU GetState")
            ("abort", "DFU Abort")
            ("wBlockNum", "Initial Block number used for download" ,\
             cxxopts::value<uint16_t>())
            ("dnload0", "DFU Download Zero Size")
            ("dnload8", "DFU Download 1 Byte" ,\
             cxxopts::value<uint8_t>())
            ("dnload16", "DFU Download 2 Byte" ,\
             cxxopts::value<uint16_t>())
            ("dnload32", "DFU Download 4 Byte" ,\
             cxxopts::value<uint32_t>())
            ("dnload64", "DFU Download 8 Byte" ,\
             cxxopts::value<uint64_t>())
            ("dnload_file", "DFU Download File")
            ("upload8", "DFU Upload 1 Byte" ,\
             cxxopts::value<uint32_t>())
            ("upload16", "DFU Upload 2 Byte" ,\
             cxxopts::value<uint32_t>())
            ("upload32", "DFU Upload 4 Byte" ,\
             cxxopts::value<uint32_t>())
            ("upload64", "DFU Upload 8 Byte" ,\
             cxxopts::value<uint32_t>())
            ("upload_file", "DFU Upload File",\
             cxxopts::value<uint32_t>());
}


void USBTestCli::ParseDfuCmds(const cxxopts::ParseResult &result)
{
    if ((!this->usb_device) || ((this->usb_device->DeviceClass() != StandardUSB::USBClassType::DFU_ST_EX) && \
                                (this->usb_device->DeviceClass() != StandardUSB::USBClassType::STD_DFU)))
        return;

    DFUClass *dfu = dynamic_cast<DFUClass *>(this->usb_device);

    DFUSetAltSetting(dfu, result);
    DFUDisplayDescriptorSet(dfu, result);
    DFUDeatch(dfu, result);
    DFUGetStatus(dfu, result);
    DFUClearStatus(dfu, result);
    DFUGetState(dfu, result);
    DFUAbort(dfu, result);
    DFUDnloadZeroLength(dfu, result);
    DFUDnload1Byte(dfu, result);
    DFUDnload2Bytes(dfu, result);
    DFUDnload4Bytes(dfu, result);
    DFUDnload8Bytes(dfu, result);
    DFUUploadDisplay1Byte(dfu, result);
    DFUUploadDisplay2Bytes(dfu, result);
    DFUUploadDisplay4Bytes(dfu, result);
    DFUUploadDisplay8Bytes(dfu, result);
    DFUDnloadFile(dfu, result);
    DFUUploadFile(dfu, result);
}


void USBTestCli::DFUSetAltSetting(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* Set Interface alt setting */
    if (result.count("set_altsetting"))
    {
        std::cout << std::endl;
        std::cout << "USB Interface Set Alt Setting:" << std::endl;

        uint8_t alt_set = result["set_altsetting"].as<uint8_t>();
        if (dfu->InterfaceSetAltSetting(0x00, alt_set))
            return;

        std::cout << "Info: USB Interface Set Alt Setting Done" << std::endl;
    }
}


void USBTestCli::DFUDisplayDescriptorSet(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* Display USB descriptors set */
    if (result.count("displaydesc"))
        dfu->DisplayDescriptorsSet();
}


void USBTestCli::DFUDeatch(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU detach */
    if (result.count("detach"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Detach:" << std::endl;
        if (dfu->DfuDetach(0x00))
            return;

        std::cout << "Info: DFU 1.1 Detach Done" << std::endl;
    }
}


void USBTestCli::DFUGetStatus(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU getstatus */
    if (result.count("getstatus"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Get Status:" << std::endl;
        DFUClass::Status status = dfu->DfuGetStatus(0x00);

        if ((status.bStatus == DFUClass::DFUStatus::statusUNKNOWN) || (status.bState == DFUClass::DFUState::stateUNKNOWN))
            return;

        dfu->DisplayDfuStatus();
    }
}


void USBTestCli::DFUClearStatus(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU clearstatus */
    if (result.count("clearstatus"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Clear Status:" << std::endl;
        if (dfu->DfuClearStatus(0x00))
            return;

        std::cout << "Info: DFU 1.1 Clear Status Done" << std::endl;
    }
}


void USBTestCli::DFUGetState(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU get state */
    if (result.count("getstate"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Get State:" << std::endl;
        if (dfu->DfuGetState(0x00) == DFUClass::DFUState::stateUNKNOWN)
            return;

        dfu->DisplayDfuState();
    }
}


void USBTestCli::DFUAbort(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU abort */
    if (result.count("abort"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Abort:" << std::endl;
        if (dfu->DfuAbort(0x00))
            return;

        std::cout << "Info: DFU 1.1 Abort Done" << std::endl;
    }
}


void USBTestCli::DFUDnloadZeroLength(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Dnload Zero Size */
    if (result.count("dnload0"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload Size Zero:" << std::endl;
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        if (dfu->DfuDownload(wBlockNum, 0x00))
            return;

        std::cout << "DFU 1.1 Donwload Size Zero Done" << std::endl;
    }
}


void USBTestCli::DFUDnload1Byte(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Dnload 1bytes */
    if (result.count("dnload8"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload 1 Byte:" << std::endl;
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        uint8_t data = result["dnload8"].as<uint8_t>();

        if(dfu->DfuDownloadData(wBlockNum, 0x00, &data, 0x01))
            return;

        std::cout << "DFU 1.1 Donwload 1 Byte Done" << std::endl;
    }
}


void USBTestCli::DFUDnload2Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Dnload 2bytes */
    if (result.count("dnload16"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload 2 Bytes:" << std::endl;
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        uint16_t value = result["dnload16"].as<uint16_t>();
        uint8_t data[2] = {static_cast<uint8_t>(static_cast<uint32_t>(value) & 0xFF),
                           static_cast<uint8_t>((static_cast<uint32_t>(value) >> 8 ) & 0xFF)};

        if(dfu->DfuDownloadData(wBlockNum, 0x00, data, 0x02))
            return;

        std::cout << "DFU 1.1 Donwload 2 Bytes Done" << std::endl;
    }
}


void USBTestCli::DFUDnload4Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Dnload 4bytes */
    if (result.count("dnload32"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload 4 Bytes:" << std::endl;
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        uint32_t value = result["dnload32"].as<uint32_t>();
        uint8_t data[4] = {static_cast<uint8_t>(value & 0xFF),
                           static_cast<uint8_t>((value >> 8 ) & 0xFF),
                           static_cast<uint8_t>((value >> 16 ) & 0xFF),
                           static_cast<uint8_t>((value >> 24 ) & 0xFF)};

        if(dfu->DfuDownloadData(wBlockNum, 0x00, data, 0x04))
            return;

        std::cout << "DFU 1.1 Donwload 4 Byte Done" << std::endl;
    }
}


void USBTestCli::DFUDnload8Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Dnload 8bytes */
    if (result.count("dnload64"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload 8 Bytes:" << std::endl;
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        uint64_t value = result["dnload64"].as<uint64_t>();
        uint8_t data[8] = {static_cast<uint8_t>(value & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 8 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 16 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 24 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 32 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 40 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 48 ) & 0xFF),
                           static_cast<uint8_t>(static_cast<uint64_t>(value >> 56 ) & 0xFF)};

        if(dfu->DfuDownloadData(wBlockNum, 0x00, data, 0x08))
            return;

        std::cout << "DFU 1.1 Donwload 8 Bytes Done" << std::endl;
    }
}


void USBTestCli::DFUUploadDisplay1Byte(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Upload in 1 Byte */
    if (result.count("upload8"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Upload and Display as 1 Byte:" << std::endl;

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        /* get the number of bytes */
        uint32_t size = result["upload8"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            std::cout << "Error: Unable to send upload cmd, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, size);

        /*upload data from device */
        if (dfu->DfuUploadData(wBlockNum, 0x00, data, size))
        {
            delete[] data;
            return;
        }

        dfu->DisplayData8(data, size);
        delete[] data;
    }
}


void USBTestCli::DFUUploadDisplay2Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Upload in 2 Byte */
    if (result.count("upload16"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Upload and Display as 2 Bytes:" << std::endl;

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        /* get the number of bytes */
        uint32_t size = result["upload16"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[2 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send upload cmd, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 2 * size);

        /*upload data from device */
        if (dfu->DfuUploadData(wBlockNum, 0x00, data, 2 * size))
        {
            delete[] data;
            return;
        }

        dfu->DisplayData16(data, 2 * size);
        delete[] data;
    }
}


void USBTestCli::DFUUploadDisplay4Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Upload in 4 Byte */
    if (result.count("upload32"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Upload and Display as 4 Bytes:" << std::endl;

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        /* get the number of bytes */
        uint32_t size = result["upload32"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[4 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send upload32, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 4 * size);

        /*upload data from device */
        if (dfu->DfuUploadData(wBlockNum, 0x00, data, 4 * size))
        {
            delete[] data;
            return;
        }

        dfu->DisplayData32(data, 4 * size);
        delete[] data;
    }
}


void USBTestCli::DFUUploadDisplay8Bytes(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU Upload in 8 Byte */
    if (result.count("upload64"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Upload and Display as 8 Bytes:" << std::endl;

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        /* get the number of bytes */
        uint32_t size = result["upload64"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[8 * size];
        if (!data)
        {
            std::cout << "Error: Unable to send upload64, Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, 8 * size);

        /*upload data from device */
        if (dfu->DfuUploadData(wBlockNum, 0x00, data, 8 * size))
        {
            delete[] data;
            return;
        }

        dfu->DisplayData64(data, 8 * size);
        delete[] data;
    }
}


void USBTestCli::DFUDnloadFile(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU 1.1 Donwload file */
    if (result.count("dnload_file"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Donwload file:" << std::endl;

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
            return ;
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

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        if (dfu->DfuDownloadData(wBlockNum, 0x00, reinterpret_cast<const uint8_t *>(const_cast<const char *>(data)), static_cast<uint32_t>(lSize)))
        {
            fclose(file);
            delete[] data;
            return;
        }

        std::cout << "Info: DFU 1.1 Donwload file: " << file_name << " Done" << std::endl;
        fclose(file);
        delete[] data;
    }
}


void USBTestCli::DFUUploadFile(DFUClass *dfu, const cxxopts::ParseResult &result)
{
    /* DFU 1.1 Upload file */
    if (result.count("upload_file"))
    {
        std::cout << std::endl;
        std::cout << "DFU 1.1 Upload file:" << std::endl;

        if (!result.count("file"))
        {
            std::cout << "Error: Missing --file option, please specify the target file" << std::endl;
            return;
        }

        /* get the file name */
        std::string file_name = result["file"].as<std::string>();

        /* Check the block number to start with */
        uint16_t wBlockNum = 0x00;
        if (!result.count("wBlockNum"))
            std::cout << "Warning: Missing wBlockNum option, proceeding with wBlockNum = 0x00" << std::endl;
        else
            wBlockNum = result["wBlockNum"].as<uint16_t>();

        /* get the number of bytes */
        uint32_t size = result["upload_file"].as<uint32_t>();

        /* allocate memory */
        uint8_t *data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            std::cout << "Error: Unable to send Upload file: " << file_name << " Memory allocation error" << std::endl;
            return;
        }
        memset(data, 0x00, size);

        /*upload data from device */
        if (dfu->DfuUploadData(wBlockNum, 0x00, data, size))
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

        /* Write data into the file */
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

        std::cout << "Info: DFU 1.1 Upload file: " << file_name << " Done" << std::endl;
    }
}


#endif
