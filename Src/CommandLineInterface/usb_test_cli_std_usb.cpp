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
#include "display_manager.h"


/* ********************************************************************************************** */
/* ***************************************** CLI Parser ***************************************** */
/* ********************************************************************************************** */
/**
 * @brief USBTestCli::InitUSBCommands
 * Define the standard usb requests' commands
 */
void USBTestCli::InitUSBCommands()
{
    options->add_options("Standard USB Options")
            /* Device handling options */
            ("list", "List connected USB devices")
            ("usb", "Connect as a USB device without taking in count the USB Class")
            ("idvendor", "the vendor id of the fdu device",\
             cxxopts::value<uint16_t>())
            ("idproduct", "the product id of the fdu device",\
             cxxopts::value<uint16_t>())
            ("timeout_c", "usb control transfer time out in ms" ,\
             cxxopts::value<unsigned int>())
            ("timeout_i", "usb interrupt transfer time out in ms" ,\
             cxxopts::value<unsigned int>())
            ("timeout_b", "usb bulk transfer time out in ms" ,\
             cxxopts::value<unsigned int>())

            /* *** */
            ("display_desc", "Display USB device & configuration descriptors")

            /* Standard device requests */
            ("dev_getstatus", "Send a standard usb device get status request")
            ("dev_clearfeat", "Send a standard usb device clear featute request")
            ("dev_setfeat", "Send a standard usb device set featute request")
            ("dev_setadd", "Send a standard usb device set address request")
            ("dev_getdesc", "Send a standard usb device get descriptor request")
            ("dev_setdesc", "Send a standard usb device set descriptor request")
            ("dev_getconfig", "Send a standard usb device get configuration request")
            ("dev_setconfig", "Send a standard usb device set configuration request")
            ("dev_getstrdesc", "Send a standard usb device get string descriptor")

            /* Standard interface requests */
            ("inter_getstatus", "Send a standard usb interface get status request")
            ("inter_clearfeat", "Send a standard usb interface clear featute request")
            ("inter_setfeat", "Send a standard usb interface set featute request")
            ("inter_setalt", "Send a standard usb interface set alternate setting")
            ("inter_getalt", "Send a standard usb interface get alternate setting")

            /* Standard endpoint requests */
            ("ep_getstatus", "Send a standard usb endpoint get status request")
            ("ep_clearfeat", "Send a standard usb endpoint clear featute request")
            ("ep_setfeat", "Send a standard usb endpoint set featute request")
            ("ep_syncframe", "Send a standard usb endpoint sync frame request")

            /* String descriptor */

            /* Standard requests options */
            ("address", "USB address",\
             cxxopts::value<uint16_t>())
            ("type", "Descriptor type, used for get/set descriptor requests",\
             cxxopts::value<uint8_t>())
            ("index", "Descriptor index, used for get/set descriptor requests",\
             cxxopts::value<uint8_t>())
            ("language", "Descriptor language, used for get/set descriptor requests",\
             cxxopts::value<uint16_t>())
            ("config", "The usb configuration to be set",\
             cxxopts::value<uint16_t>())
            ("interface", "The interface index on which to opertaion will be executed",\
             cxxopts::value<uint16_t>())
            ("altsetting", "The interface's alternate setting to be set",\
             cxxopts::value<uint8_t>())
            ("endpoint", "The endpoint index on which to opertaion will be executed",\
             cxxopts::value<uint16_t>())
            ("feature", "The feature to be disabled or enabled",\
             cxxopts::value<uint16_t>())

            /* interface communication option */
            ("claim_interface", "Request the ownership of the given interface from the host OS")
            ("release_interface", "Release a previusly claimed interface")
            ("reset", "Release a previusly claimed interface")

            /* Control requests options */
            ("control", "Send/receive data via control end point(0x00)")
            ("bmRequestType", "the request type field for the setup packet",\
             cxxopts::value<uint8_t>())
            ("bRequest", "the request field for the setup packet",\
             cxxopts::value<uint8_t>())
            ("wValue", "the value field for the setup packet",\
             cxxopts::value<uint16_t>())
            ("wIndex", "the index field for the setup packet",\
             cxxopts::value<uint16_t>())

            /* Bulk/Interrupt requests options */
            ("bulk", "Send/receive data via bulk transfer")
            ("interrupt", "Send/receive data via interrupt transfer")

            /* data type for transfert */
            ("file", "file from/to which the data will be transfered" ,\
             cxxopts::value<std::string>())
            ("size", "the data buffer length",\
             cxxopts::value<size_t>())
            ("data0", "Data to be transfered is NULL and size = 0x00")
            ("data8", "Data to be stransfered has a size of 1 byte",\
             cxxopts::value<uint8_t>())
            ("data16", "Data to be stransfered has a size of 2 bytes",\
             cxxopts::value<uint16_t>())
            ("data32", "Data to be stransfered has a size of 4 bytes",\
             cxxopts::value<uint32_t>())
            ("data64", "Data to be stransfered has a size of 8 bytes",\
             cxxopts::value<uint64_t>())

            /* Displaying options */
            ("display8", "Upon data transfer success diplay data as 8bits")
            ("display16", "Upon data transfer success diplay data as 16bits")
            ("display32", "Upon data transfer success diplay data as 32bits")
            ("display64", "Upon data transfer success diplay data as 64bits")
            ;
}


/**
 * @brief USBTestCli::DisplayUSBHelp
 */
void USBTestCli::DisplayUSBHelp()
{
    std::stringstream stream;
    stream << "USB Standard options\n";
    /* **** */
    stream << "\t    --list                  Display the currently attached devices\n";
    stream << "\t    --usb                   Connect as a USB device without taking in count \n";
    stream << "\t                            the USB Class\n";
    stream << "\t    --idvendor              The vendor id of the usb device\n";
    stream << "\t    --idproduct             The product id of the usb device\n";
    stream << "\t    --timeout_c             USB control transfer timeout in ms\n";
    stream << "\t    --timeout_b             USB bulk transfer timeout in ms\n";
    stream << "\t    --timeout_i             USB interrupt transfer timeout in ms\n";
    stream << "\t    --display_desc          Display device & configuration descriptors\n";
    /* **** */
    stream << "\t    --dev_getstatus         Send a usb device get status request\n";
    stream << "\t    --dev_clearfeat         Send a usb device clear featute request\n";
    stream << "\t    --dev_setfeat           Send a usb device set featute request\n";
    stream << "\t    --dev_setadd            Send a usb device set address request\n";
    stream << "\t    --dev_getdesc           Send a usb device get descriptor request\n";
    stream << "\t    --dev_setdesc           Send a usb device set descriptor request\n";
    stream << "\t    --dev_getconfig         Send a usb device get configuration request\n";
    stream << "\t    --dev_setconfig         Send a usb device set configuration request\n";
    stream << "\t    --dev_getstrdesc        Send a standard usb device get string descriptor\n";
    /* **** */
    stream << "\t    --inter_getstatus       Send a usb interface get status request\n";
    stream << "\t    --inter_clearfeat       Send a usb interface clear featute request\n";
    stream << "\t    --inter_setfeat         Send a usb interface set featute request\n";
    stream << "\t    --inter_setalt          Send a usb interface set alternate setting req\n";
    stream << "\t    --inter_getalt          Send a usb interface get alternate setting req\n";
    /* **** */
    stream << "\t    --ep_getstatus          Send a usb end point get status request\n";
    stream << "\t    --ep_clearfeat          Send a usb end point clear featute request\n";
    stream << "\t    --ep_setfeat            Send a usb end point set featute request\n";
    stream << "\t    --ep_syncframe          Send a usb end point sync frame request\n";
    /* **** */
    stream << "\t    --address               The usb address\n";
    stream << "\t    --type                  The usb descriptor type\n";
    stream << "\t    --index                 The usb descriptor index\n";
    stream << "\t    --language              The usb descriptor language\n";
    stream << "\t    --config                The usb configuration\n";
    stream << "\t    --interface             The interface index\n";
    stream << "\t    --altsetting            The interface's alternate setting index\n";
    stream << "\t    --endpoint              The endpoint index\n";
    stream << "\t    --feature               The feature index\n";
    /* **** */
    stream << "\t    --claim_interface       Request the ownership of the given interface\n";
    stream << "\t    --release_interface     Release the previously claimed interface\n";
    stream << "\t    --reset                 Perform a usb port reset\n";
    /* **** */
    stream << "\t    --control               Send/receive data via control end point(0x00)\n";
    stream << "\t    --bmRequestType         The request type field for the control packet\n";
    stream << "\t    --bRequest              The request field for the control packet\n";
    stream << "\t    --wValue                The value field for the control packet\n";
    stream << "\t    --wIndex                The index field for the control packet\n";
    /* **** */
    stream << "\t    --bulk                  Exchange data via bulk transfer packet\n";
    stream << "\t    --interrupt             Exchange data via interrupt transfer\n";
    /* **** */
    stream << "\t    --file                  File from/to which to data will be transfered\n";
    stream << "\t    --size                  The data buffer length\n";
    stream << "\t    --data0                 Data to be transfer is NULL, size = 0\n";
    stream << "\t    --data8                 Data to be transfer is a byte, size = 1\n";
    stream << "\t    --data16                Data to be transfer is a half word, size = 2\n";
    stream << "\t    --data32                Data to be transfer is a word, size = 4\n";
    stream << "\t    --data64                Data to be transfer is a double word, size = 8\n";
    /* **** */
    stream << "\t    --dislpay8              Upon data transfer success diplay data as 8bits\n";
    stream << "\t    --dislpay16             Upon data transfer success diplay data as 16bits\n";
    stream << "\t    --dislpay32             Upon data transfer success diplay data as 32bits\n";
    stream << "\t    --dislpay64             Upon data transfer success diplay data as 64bits\n";
    cli_dm->PrintMessage(DisplayManager::MessageType::BASIC_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::ParseUSBCmds
 * try to match the Standard USB Options defined in
 * InitUSBCommands, and than proceed to execute them
 * @param result cli parser
 */
void USBTestCli::ParseUSBCmds(const cxxopts::ParseResult &result)
{
    if(result.count("list"))
        StandardUSB::ListUSBDevices();

    if(result.count("timeout_c"))
    {
        unsigned int timeout = result["timeout_c"].as<unsigned int>();
        StandardUSB::CtrTimeOut(timeout);
        cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                             "USB control transfer timeout set to: " + std::to_string(timeout) +
                             " ms");
    }

    if(result.count("timeout_i"))
    {
        unsigned int timeout = result["timeout_i"].as<unsigned int>();
        StandardUSB::IntTimeOut(timeout);
        cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                             "USB interrupt transfer timeout set to: " + std::to_string(timeout) +
                             " ms");
    }

    if(result.count("timeout_b"))
    {
        unsigned int timeout = result["timeout_b"].as<unsigned int>();
        StandardUSB::BulkTimeOut(timeout);
        cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                             "USB bulk transfer timeout set to: " + std::to_string(timeout) +
                             " ms");
    }

    if(result.count("usb"))
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

        /* init the usb device objects */
        ConnectUSB(idvendor, idproduct);
    }

    if (!this->usb_device)
        return;

    DisplayDescriptors(result);
    GetDeviceStatus(result);
    ClearDeviceFeature(result);
    SetDeviceFeature(result);
    SetDeviceAddress(result);
    GetDeviceDesriptor(result);
    SetDeviceDesriptor(result);
    GetDeviceConfig(result);
    GetStringDescriptor(result);
    SetDeviceConfig(result);
    GetInterfaceStatus(result);
    ClearInterfaceFeature(result);
    SetInterfaceFeature(result);
    SetInterfaceAltSetting(result);
    GetInterfaceAltSetting(result);
    GetEndpointStatus(result);
    ClearEndpointFeature(result);
    SetEndpointFeature(result);
    SyncEndpointFrame(result);
    ClaimInterface(result);
    ReleaseInterface(result);
    ResetDevice(result);
    ControlTransfer(result);
    BulkTransfer(result);
    InterruptTransfer(result);
}


/**
 * @brief USBTestCli::EstablishConnection
 * Close the usb device if it was previously opened and
 * trys to open the device according to its class type,
 * idVendor and idProduct
 * @param type StandardUSB::USBClassType
 * @param idVendor usb device idVendor
 * @param idProduct usb device idProduct
 */
void USBTestCli::ConnectUSB(uint16_t idVendor, uint16_t idProduct)
{
    /* init the usb device objects */
    if (usb_device)
    {
        delete usb_device;
        usb_device = nullptr;
    }

    usb_device = new(std::nothrow) StandardUSB(idVendor, idProduct);
    if (!usb_device)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Unable to initialize the usb device, Mmeory allocation error");
        return;
    }

    /* open the usb device */
    if (usb_device->OpenDevice())
    {
        delete usb_device;
        usb_device = nullptr;
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "Connection established");
}


/**
 * @brief USBTestCli::DisplayDescriptors
 * Display USB device descriptor, current configuration descriptor,
 * interfaces descriptors and endpoints descriptors.
 * Class specific descriptor will be displayed as extra data.
 * @param result cli parser
 */
void USBTestCli::DisplayDescriptors(const cxxopts::ParseResult &result)
{
    if (!result.count("display_desc"))
        return;

    this->usb_device->DisplayDescriptorsSet();
}


/**
 * @brief USBTestCli::GetDeviceStatus
 * Send a standard usb get device status
 * @param result cli parser
 */
void USBTestCli::GetDeviceStatus(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_getstatus"))
        return;

    uint16_t status;
    if (this->usb_device->DeviceGetStatus(status))
        return;

    std::stringstream stream;
    stream << "USB device status: 0x" << std::hex << std::setw(4) << std::setfill('0') << status;
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::ClearDeviceFeature
 * Send a standard usb clear device feature
 * @param result cli parser
 */
void USBTestCli::ClearDeviceFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_clearfeat"))
        return;

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }

    uint16_t feature = result["feature"].as<uint16_t>();
    if (this->usb_device->DeviceClearFeature(feature))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "USB clear device feature Done");
}


/**
 * @brief USBTestCli::SetDeviceFeature
 * Send a standard usb set device feature
 * @param result cli parser
 */
void USBTestCli::SetDeviceFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_setfeat"))
        return;

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }

    uint16_t feature = result["feature"].as<uint16_t>();
    if (this->usb_device->DeviceSetFeature(feature))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "USB set device feature Done");
}


/**
 * @brief USBTestCli::SetDeviceAddress
 * Send a standard usb set device address
 * @param result cli parser
 */
void USBTestCli::SetDeviceAddress(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_setadd"))
        return;

    if (!result.count("address"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --address option:");
        return;
    }

    uint16_t address = result["address"].as<uint16_t>();
    if (this->usb_device->DeviceSetAddress(address))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "USB set device address Done");
}


/**
 * @brief USBTestCli::GetDeviceDesriptor
 * Send a standard usb device get descriptor
 * @param result cli parser
 */
void USBTestCli::GetDeviceDesriptor(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_getdesc"))
        return;

    /* get descriptor type */
    if (!result.count("type"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --type option");
        return;
    }
    uint8_t type = result["type"].as<uint8_t>();

    /* get descriptor index */
    if (!result.count("index"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --index option");
        return;
    }
    uint8_t index = result["index"].as<uint8_t>();

    uint16_t language = 0x409;
    if (!result.count("language"))
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Missing --language option, proceeding with value 0x409");
    else
        language = result["language"].as<uint16_t>();

    /* get descriptor max length */
    if (!result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --size option");
        return;
    }
    size_t size = result["size"].as<size_t>();

    /* allocate memory */
    uint8_t *data = new(std::nothrow) uint8_t[size];
    if (!data)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "USB device get descriptor failed, memory allocation error");
        return;
    }
    std::memset(data, 0x00, size);

    /* receive data */
    int result_l = this->usb_device->DeviceGetDescriptor(type, index, language, data, \
                                                       static_cast<uint16_t>(size));
    if (result_l < 0)
    {
        delete[] data;
        return;
    }

    if (static_cast<size_t>(result_l) != size)
    {
        std::stringstream stream;
        stream << "The actual transfered data length is :0x" << std::hex << std::setw(4)
               << std::setfill('0') << result_l;
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE, stream.str());
        size = static_cast<size_t>(result_l);
    }


    /* write to file if any */
    if (result.count("file"))
    {
        std::string file_n = result["file"].as<std::string>();
        this->WriteBinFile(file_n, data, size);
    }

    /* display data */
    if (result.count("display16"))
        cli_dm->DisplayData16(data, size);
    else if (result.count("display32"))
        cli_dm->DisplayData32(data, size);
    else if (result.count("display64"))
        cli_dm->DisplayData64(data, size);
    else
        cli_dm->DisplayData8(data, size);

    delete[] data;
}


/**
 * @brief USBTestCli::SetDeviceDesriptor
 * Send a standard usb device set descriptor
 * @param result cli parser
 */
void USBTestCli::SetDeviceDesriptor(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_setdesc"))
        return;

    /* get descriptor type */
    if (!result.count("type"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --type option");
        return;
    }
    uint8_t type = result["type"].as<uint8_t>();

    /* get descriptor index */
    if (!result.count("index"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --index option");
        return;
    }
    uint8_t index = result["index"].as<uint8_t>();

    uint16_t language = 0x409;
    if (!result.count("language"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                             "Missing --language option, proceeding with value 0x409");
    }
    else
        language = result["language"].as<uint16_t>();

    /* get descriptor max length */
    if (!result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --size option");
        return;
    }
    size_t size = result["size"].as<size_t>();

    if (!result.count("file"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --file option");
        return;
    }

    std::string file_n = result["file"].as<std::string>();
    size_t len = 0x00;
    uint8_t *data = this->ReadBinFile(file_n, len);
    if (!data)
        return;

    if (size > len)
        size = len;

    /* send data */
    int result_l = this->usb_device->DeviceSetDescriptor(type, index, language, data, \
                                                       static_cast<uint16_t>(size));
    if (result_l < 0)
    {
        delete[] data;
        return;
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "USB device set descriptor Done");
    delete[] data;
}


/**
 * @brief USBTestCli::GetDeviceConfig
 * * Send a standard usb get device configuration
 * @param result cli parser
 */
void USBTestCli::GetDeviceConfig(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_getconfig"))
        return;

    uint8_t config = 0x00;
    if (this->usb_device->DeviceGetCongiguration(config))
        return;

    std::stringstream stream;
    stream << "USB current device configuration: 0x"<< std::hex << std::setw(2) << std::setfill('0')
           << static_cast<uint32_t>(config);
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::SetDeviceConfig
 * Send a standard usb set device configuration
 * @param result cli parser
 */
void USBTestCli::SetDeviceConfig(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_setconfig"))
        return;

    if (!result.count("config"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --config option");
        return;
    }

    uint16_t config = result["config"].as<uint16_t>();
    if (this->usb_device->DeviceSetCongiguration(config))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "USB set device configuration Done");
}


/**
 * @brief USBTestCli::GetStringDescriptor
 * Send a device get string descriptor request
 * @param result cli parser
 */
void USBTestCli::GetStringDescriptor(const cxxopts::ParseResult &result)
{
    if (!result.count("dev_getstrdesc"))
        return;

    if (!result.count("index"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --index option");
        return;
    }
    uint8_t index = result["index"].as<uint8_t>();

    if (!result.count("language"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --language option");
        return;
    }
    uint16_t language = result["language"].as<uint16_t>();

    std::string str = this->usb_device->GetStringDescriptor(index, language);
    if (str.size())
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                             "String descriptor: " + str);
    }
}


/**
 * @brief USBTestCli::GetInterfaceStatus
 * Send a standard usb get interface status
 * @param result cli parser
 */
void USBTestCli::GetInterfaceStatus(const cxxopts::ParseResult &result)
{
    if (!result.count("inter_getstatus"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }

    uint16_t interface = result["interface"].as<uint16_t>();
    uint16_t status = 0x00;
    if (this->usb_device->InterfaceGetStatus(interface, status))
        return;

    std::stringstream stream;
    stream << "USB interface: 0x" << std::hex << std::setw(2) << std::setfill('0') << interface
           << " status: 0x" << std::hex << std::setw(4) << std::setfill('0') << status;
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::ClearInterfaceFeature
 * Send a standard usb clear interface feature
 * @param result cli parser
 */
void USBTestCli::ClearInterfaceFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("inter_clearfeat"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    uint16_t interface = result["interface"].as<uint16_t>();

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }
    uint16_t feature = result["feature"].as<uint16_t>();

    if (this->usb_device->InterfaceClearFeature(interface, feature))
        return;

    std::stringstream stream;
    stream << "USB clear interface: 0x"<< std::hex << std::setw(2) << std::setfill('0') << interface
           << " feature: 0x" << std::hex << std::setw(4) << std::setfill('0') << feature << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::SetInterfaceFeature
 * Send a standard usb set interface feature
 * @param result cli parser
 */
void USBTestCli::SetInterfaceFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("inter_setfeat"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    uint16_t interface = result["interface"].as<uint16_t>();

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }
    uint16_t feature = result["feature"].as<uint16_t>();

    if (this->usb_device->InterfaceSetFeature(interface, feature))
        return;

    std::stringstream stream;
    stream << "USB set interface: 0x"<< std::hex << std::setw(2) << std::setfill('0') << interface
           << " feature: 0x" << std::hex << std::setw(4) << std::setfill('0') << feature << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::SetInterfaceAltSetting
 * Send a standard usb set interface alternate setting
 * @param result cli parser
 */
void USBTestCli::SetInterfaceAltSetting(const cxxopts::ParseResult &result)
{
    if (!result.count("inter_setalt"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    uint16_t interface = result["interface"].as<uint16_t>();

    if (!result.count("altsetting"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --altsetting option:");
        return;
    }
    uint8_t altsetting = result["altsetting"].as<uint8_t>();

    if (this->usb_device->InterfaceSetAltSetting(interface, altsetting))
        return;

    std::stringstream stream;
    stream << "USB set interface: 0x"<< std::hex << std::setw(4) << std::setfill('0') << interface
           << " alternate setting: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<uint32_t>(altsetting) << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::GetInterfaceAltSetting
 * Send a standard usb get interface alternate setting
 * @param result cli parser
 */
void USBTestCli::GetInterfaceAltSetting(const cxxopts::ParseResult &result)
{
    if (!result.count("inter_getalt"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    uint16_t interface = result["interface"].as<uint16_t>();

    uint8_t altsetting = 0x00;
    if (this->usb_device->InterfaceGetAltSetting(interface, altsetting))
        return;

    std::stringstream stream;
    stream << "USB interface: 0x"<< std::hex << std::setw(4) << std::setfill('0') << interface
           << " alternate setting: 0x" << std::hex << std::setw(4) << std::setfill('0')
           << static_cast<uint32_t>(altsetting);
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::GetEndpointStatus
 * Send a standard usb get endpoint status
 * @param result cli parser
 */
void USBTestCli::GetEndpointStatus(const cxxopts::ParseResult &result)
{
    if (!result.count("ep_getstatus"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }

    uint16_t ep = result["endpoint"].as<uint16_t>();
    uint16_t status = 0x00;
    if (this->usb_device->EndpointGetStatus(ep, status))
        return;

    std::stringstream stream;
    stream << "USB endpoint: 0x" << std::hex << std::setw(4) << std::setfill('0') << ep
           << " status: 0x" << std::hex << std::setw(4) << std::setfill('0') << status;
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::ClearEndpointFeature
 * Send a standard usb clear endpoint feature
 * @param result cli parser
 */
void USBTestCli::ClearEndpointFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("ep_clearfeat"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }
    uint16_t endpoint = result["endpoint"].as<uint16_t>();

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }
    uint16_t feature = result["feature"].as<uint16_t>();

    if (this->usb_device->EndpointClearFeature(endpoint, feature))
        return;

    std::stringstream stream;
    stream << "USB clear endpoint: 0x"<< std::hex << std::setw(4) << std::setfill('0') << endpoint
           << " feature: 0x" << std::hex << std::setw(4) << std::setfill('0') << feature << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::SetEndpointFeature
 * Send a standard usb set endpoint feature
 * @param result cli parser
 */
void USBTestCli::SetEndpointFeature(const cxxopts::ParseResult &result)
{
    if (!result.count("ep_setfeat"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }
    uint16_t endpoint = result["endpoint"].as<uint16_t>();

    if (!result.count("feature"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --feature option:");
        return;
    }
    uint16_t feature = result["feature"].as<uint16_t>();

    if (this->usb_device->EndpointSetFeature(endpoint, feature))
        return;

    std::stringstream stream;
    stream << "USB set endpoint: 0x"<< std::hex << std::setw(4) << std::setfill('0') << endpoint
           << " feature: 0x" << std::hex << std::setw(4) << std::setfill('0') << feature << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::SyncEndpointFrame
 * Send a standard usb synchronize endpoint frame
 * @param result cli parser
 */
void USBTestCli::SyncEndpointFrame(const cxxopts::ParseResult &result)
{
    if (!result.count("ep_syncframe"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }
    uint16_t endpoint = result["endpoint"].as<uint16_t>();

    uint16_t frame = 0x00;
    if (this->usb_device->EndpointSynchFrame(endpoint, frame))
        return;

    std::stringstream stream;
    stream << "USB sync endpoint: 0x"<< std::hex << std::setw(4) << std::setfill('0') << endpoint
           << " frame: 0x" << std::hex << std::setw(4) << std::setfill('0') << frame << " Done";
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, stream.str());
}


/**
 * @brief USBTestCli::ClaimInterface
 * instruct the underlying operating system that our
 * application wishes to take ownership of the interface
 * @param result cli parser
 */
void USBTestCli::ClaimInterface(const cxxopts::ParseResult &result)
{
    if (!result.count("claim_interface"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    /* Get the List of interfaces to claim */
    uint16_t interface = result["interface"].as<uint16_t>();
    if (this->usb_device->USBClaimInterface(interface))
        return;

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "Claim usb device interface: " + std::to_string(interface) + " Done");
}


/**
 * @brief USBTestCli::ReleaseInterface
 * Release previously claimed interfaces, this must be done before closing the device
 * @param result cli parser
 */
void USBTestCli::ReleaseInterface(const cxxopts::ParseResult &result)
{
    if (!result.count("release_interface"))
        return;

    if (!result.count("interface"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --interface option");
        return;
    }
    /* Get the List of interfaces to release */
    uint16_t interface = result["interface"].as<uint16_t>();
    this->usb_device->USBReleaseInterface(interface);
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,
                         "Release usb device interface: " + std::to_string(interface) + " Done");
}


/**
 * @brief USBTestCli::ResetDevice
 * Perform a USB port reset to reinitialize a device
 * @param result cli parser
 */
void USBTestCli::ResetDevice(const cxxopts::ParseResult &result)
{
    if (!result.count("reset"))
        return;

    this->usb_device->USBReset();
    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "USB reset device Done");
}


/**
 * @brief USBTestCli::GetDataCli
 * Extract data from data8, data16, data32 and data64 options
 * these option are used for different control, interrupt and
 * bulk transfer
 * @param result cli parser
 * @param size output parameter for the actual data stream size
 * @return data pointer
 */
uint8_t *USBTestCli::GetDataCli(const cxxopts::ParseResult &result, size_t &size)
{
    /* get the default size and data from their options */
    uint64_t value = 0x00;
    if (result.count("data8"))
    {
        size = 0x1;
        value = result["data8"].as<uint8_t>();
    }
    else if(result.count("data16"))
    {
        size = 0x2;
        value = result["data16"].as<uint16_t>();
    }
    else if (result.count("data32"))
    {
        size = 0x4;
        value = result["data32"].as<uint32_t>();
    }
    else if (result.count("data64"))
    {
        size = 0x8;
        value = result["data64"].as<uint64_t>();
    }

    /* allocate and fill in the memory */
    uint8_t *data = new(std::nothrow) uint8_t[size];
    if(!data)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "USB transfer failed, Memory allocation error");
        return nullptr;
    }

    for (size_t index = 0; index < size; index++)
        *(data + index) = static_cast<uint8_t>((value >> (index * 8)) & 0xFF);

    /* check the --size option */
    if (result.count("size"))
    {
        size_t l_size = result["size"].as<size_t>();
        if (!l_size)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "Option --size can not be zero");
            delete[] data;
            return nullptr;
        }
        else if (l_size > size)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                                 "Ignoring the --size option, value too big for data length");
        }

        else
            size = l_size;
    }

    return data;
}


/**
 * @brief USBTestCli::GetDataFile
 * Extract data drom file if the request is a host-to-device transfer(--ep_in), otherwise
 * allocate the requested data size and output the file path in which the data
 * will be written.
 * @param result cli parser
 * @param size output parameter for the actual data stream size
 * @param file_name file path to which the data will be written if its a download request
 * @return data pointer
 */
uint8_t *USBTestCli::GetDataFile(const cxxopts::ParseResult &result, size_t &size)
{
    /* get the file path and open it depending on the --ep_in option */
    std::string file_path = result["file"].as<std::string>();

    size_t size_l = 0x00;
    uint8_t *data = ReadBinFile(file_path, size_l);
    if (!data)
        return nullptr;

    size = size_l;
    /* check the --size option */
    if (result.count("size"))
    {
        size_t size_l = result["size"].as<size_t>();
        if (size_l > size)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE,
                                 "Ignoring --size option, value too big for file size");
        }

        size = size_l;
    }
    return data;
}


/**
 * @brief USBTestCli::ControlTransfer
 * Send/Receive data buy issuing a usb control transfer
 * @param result cli parser
 */
void USBTestCli::ControlTransfer(const cxxopts::ParseResult &result)
{
    if (!result.count("control"))
        return;

    /* check bmRequestType */
    uint8_t bmrequesttype = 0x00;
    if (!result.count("bmRequestType"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --bmRequestType option");
        return;
    }
    bmrequesttype = result["bmRequestType"].as<uint8_t>();
    uint8_t transfer_direction = static_cast<uint8_t>(bmrequesttype & 0x80);

    /* check bRequest */
    uint8_t brequest = 0x00;
    if (!result.count("bRequest"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --bRequest option");
        return;
    }
    brequest = result["bRequest"].as<uint8_t>();

    /* check wValue */
    uint16_t wvalue = 0x00;
    if (!result.count("wValue"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --wValue option");
        return;
    }
    wvalue = result["wValue"].as<uint16_t>();

    /* check wIndex */
    uint16_t windex = 0x00;
    if (!result.count("wIndex"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --wIndex option");
        return;
    }
    windex = result["wIndex"].as<uint16_t>();

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    /* check the size for device to host transfer */
    if (transfer_direction && !result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --size option");
        return;
    }

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
    else if (result.count("file") && !result.count("data0") && !transfer_direction)
    {
        data = GetDataFile(result, size);
        if (!data)
            return;
    }
    /* data transfer from device to host */
    else if (transfer_direction)
    {
        size = result["size"].as<size_t>();
        data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "USB control transfer failed, Memory allocation error");
            return ;
        }
        std::memset(data, 0x00, size);

    }
    else
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --data0(8/16/32/64) or --file options");
        return;
    }

    /* send/receive data */
    int result_l = this->usb_device->USBControlTransfer(bmrequesttype, brequest, wvalue, windex,\
                                                        data, static_cast<uint16_t>(size));
    if (result_l < 0)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "USB control transfer failed, " +
                             this->usb_device->GetStrError(result_l));
        delete[] data;
        return;
    }

    /* check the actual size of transfered data */
    if (static_cast<size_t>(result_l) < size)
    {
        size = static_cast<uint16_t>(result_l);
        std::stringstream stream;
        stream << std::hex << std::setfill ('0') << "The actual size of transfered data is :0x"
               << std::setw(4) << size;
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE, stream.str());
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE,"USB control transfer Done");

    /* write to the file */
    if (result.count("file") && transfer_direction)
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


/**
 * @brief USBTestCli::BulkTransfer
 * Send/Receive data buy issuing a usb bulk transfer
 * @param result cli parser
 */
void USBTestCli::BulkTransfer(const cxxopts::ParseResult &result)
{
    if (!result.count("bulk"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }
    uint8_t ep = result["endpoint"].as<uint8_t>();
    uint8_t transfer_direction = static_cast<uint8_t>(ep & 0x80);

    /* check the size for device to host transfer */
    if (transfer_direction && !result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --size option");
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    /* target file if any */
    std::string file_name;

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
    /* data will transfered from/to file */
    else if (result.count("file") && !result.count("data0") && !transfer_direction)
    {
        data = GetDataFile(result, size);
        if (!data)
            return;
    }

    else if (transfer_direction)
    {
        size = result["size"].as<size_t>();
        data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "USB Bulk transfer failed, Memory allocation error");
            return ;
        }
        std::memset(data, 0x00, size);

    }
    else
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --data0(8/16/32/64) or --file options");
        return;
    }

    /* send/receive data */
    int result_l = this->usb_device->USBBulkTransfer(ep, data, static_cast<int>(size));
    if (result_l < 0)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "USB Bulk transfer failed, " +
                             this->usb_device->GetStrError(result_l));
        return;
    }

    /* check the actual size of transfered data */
    if (static_cast<size_t>(result_l) < size)
    {
        size = static_cast<uint16_t>(result_l);
        std::stringstream stream;
        stream << std::hex << std::setfill ('0') << "The actual size of transfered data is :0x"
               << std::setw(4) << size;
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE, stream.str());
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "USB Bulk transfer Done");

    /* write to the file */
    if (result.count("file") && transfer_direction)
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


/**
 * @brief USBTestCli::InterruptTransfer
 * Send/Receive data buy issuing a usb interrupt transfer
 * @param result cli parser
 */
void USBTestCli::InterruptTransfer(const cxxopts::ParseResult &result)
{
    if (!result.count("interrupt"))
        return;

    if (!result.count("endpoint"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --endpoint option");
        return;
    }
    uint8_t ep = result["endpoint"].as<uint8_t>();
    uint8_t transfer_direction = static_cast<uint8_t>(ep & 0x80);

    /* check the size for device to host transfer */
    if (transfer_direction && !result.count("size"))
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE, "Missing --size option");
    }

    /* check the data to be sent */
    uint8_t *data = nullptr;
    size_t size = 0x00;

    /* target file if any */
    std::string file_name;

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
    /* data will transfered from/to file */
    else if (result.count("file") && !result.count("data0") && !transfer_direction)
    {
        data = GetDataFile(result, size);
        if (!data)
            return;
    }

    else if (transfer_direction)
    {
        size = result["size"].as<size_t>();
        data = new(std::nothrow) uint8_t[size];
        if (!data)
        {
            cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                                 "USB interrupt transfer failed, Memory allocation error");
            return ;
        }
        std::memset(data, 0x00, size);

    }
    else
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "Missing --data0(8/16/32/64) or --file options");
        return;
    }

    /* send/receive data */
    int result_l = this->usb_device->USBInterruptTransfer(ep, data, static_cast<int>(size));
    if (result_l < 0)
    {
        cli_dm->PrintMessage(DisplayManager::MessageType::ERROR_MESSAGE,
                             "USB interrupt transfer failed, " +
                             this->usb_device->GetStrError(result_l));
        return;
    }

    /* check the actual size of transfered data */
    if (static_cast<size_t>(result_l) < size)
    {
        size = static_cast<uint16_t>(result_l);
        std::stringstream stream;
        stream << std::hex << std::setfill ('0') << "The actual size of transfered data is :0x"
               << std::setw(4) << size;
        cli_dm->PrintMessage(DisplayManager::MessageType::WARNING_MESSAGE, stream.str());
    }

    cli_dm->PrintMessage(DisplayManager::MessageType::INFO_MESSAGE, "USB Interrupt transfer Done");
    /* get the nbr of bytes that were actually transferred */

    /* write to the file */
    if (result.count("file") && transfer_direction)
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
