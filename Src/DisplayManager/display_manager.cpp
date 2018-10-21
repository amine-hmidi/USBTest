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
#include <iomanip>
#include <sstream>

/* C Includes */

/* User Includes */
#include "display_manager.h"


DisplayManager* DisplayManager::display_manager = nullptr;


DisplayManager* DisplayManager::Instance()
{
    if (!display_manager)
        display_manager = new(std::nothrow) DisplayManager();

    return  display_manager;
}


void DisplayManager::Destroy()
{
    delete display_manager;
    display_manager = nullptr;
}


void DisplayManager::PrintMessage(DisplayManager::MessageType type, const std::string& message)
{
    if (type == DisplayManager::MessageType::INFO_MESSAGE)
        std::cout << "Info: ";
    else if (type == DisplayManager::MessageType::WARNING_MESSAGE)
        std::cout << "Warning: ";
    else if (type == DisplayManager::MessageType::ERROR_MESSAGE)
        std::cout << "Error :";

    std::cout << message << "\n";
}


void DisplayManager::PrintMessage(DisplayManager::MessageType type, const char * message)
{
    if (type == DisplayManager::MessageType::INFO_MESSAGE)
        std::cout << "Info: ";
    else if (type == DisplayManager::MessageType::WARNING_MESSAGE)
        std::cout << "Warning: ";
    else if (type == DisplayManager::MessageType::ERROR_MESSAGE)
        std::cout << "Error :";

    std::cout << std::string(message) << "\n";
}


void DisplayManager::DisplayData8(uint8_t *data, size_t size)
{
    std::string header = "OFFSET      0x00 0x01 0x02 0x03 0x04 0x05 0x06 0x07 0x08 0x09 0x0A 0x0B "
                         "0x0C 0x0D 0x0E 0x0F";

    PrintMessage(MessageType::INFO_MESSAGE, header);
    PrintMessage(MessageType::INFO_MESSAGE, "\n");

    size_t nbr = size / 0x10;
    uint32_t remain = size % 0x10;

    for (size_t i = 0; i < nbr; i++)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x10) << "  ";
        for (uint32_t j = 0; j < 0x10; j++)
        {
            stream << "0x" << std::setw(2) << static_cast<uint32_t>(*(data + (i * 0x10) + j))
                   << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }

    if (remain)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(0x10 * nbr) << "  ";
        for (uint32_t j = 0; j < remain; j++)
        {
            stream << "0x" << std::setw(2) << static_cast<uint32_t>(*(data + (nbr * 0x10) + j))
                   << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }
}


void DisplayManager::DisplayData16(uint8_t *data, size_t size)
{
    std::string header = "OFFSET      0x0000 0x0002 0x0004 0x0006 0x0008 0x000A 0x000C 0x000E";

    PrintMessage(MessageType::INFO_MESSAGE, header);
    PrintMessage(MessageType::INFO_MESSAGE, "\n");

    size_t nbr = size / 0x10;
    uint32_t remain = size % 0x10;

    for (size_t i = 0; i < nbr; i++)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x10) << "  ";
        for (uint32_t j = 0; j < 0x10; j += 2)
        {
            uint16_t value = static_cast<uint16_t>((*(data + (i * 0x10) + j)) | \
                             (static_cast<uint32_t>((*(data + (i * 0x10) + j + 1))) << 8));
            stream << "0x" << std::setw(4) << static_cast<uint32_t>(value) << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }

    if (remain)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(0x10 * nbr) << "  ";
        for (uint32_t j = 0; j < remain; j += 2)
        {
            uint16_t value = static_cast<uint16_t>(*(data + (nbr * 0x10) + j));
            if ((j + 1) < remain)
                value |=  static_cast<uint16_t>((static_cast<uint32_t>
                                                 ((*(data + (nbr * 0x10) + j + 1))) << 8));


            stream << "0x" << std::setw(4) << static_cast<uint32_t>(value) << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }
}


void DisplayManager::DisplayData32(uint8_t *data, size_t size)
{
    std::string header = "OFFSET      0x00000000 0x00000004 0x00000008 0x0000000C 0x00000010"
                         " 0x00000014 0x00000018 0x0000001C";

    PrintMessage(MessageType::INFO_MESSAGE, header);
    PrintMessage(MessageType::INFO_MESSAGE, "\n");

    size_t nbr = size / 0x20;
    uint32_t remain = size % 0x20;

    for (size_t i = 0; i < nbr; i++)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x20) << "  ";
        for (uint32_t j = 0; j < 0x20; j += 4)
        {
            uint32_t value = (*(data + (i * 0x20) + j)) | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint32_t>((*(data + (i * 0x20) + j + 3)))) << 24);
            stream << "0x" << std::setw(8) << static_cast<uint32_t>(value) << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }

    if (remain)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(0x20 * nbr) << "  ";
        for (uint32_t j = 0; j < remain; j += 4)
        {
            uint32_t value = (*(data + (nbr * 0x20) + j));
            if ((j + 1) < remain)
                value |= ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 1)))) << 8);
            if ((j + 2) < remain)
                value |= ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 2)))) << 16);
            if ((j + 3) < remain)
                value |= ((static_cast<uint32_t>((*(data + (nbr * 0x20) + j + 3)))) << 24);

            stream << "0x" << std::setw(8) << static_cast<uint32_t>(value) << " ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }
}


void DisplayManager::DisplayData64(uint8_t *data, size_t size)
{
    std::string header = "OFFSET      0x0000000000000000  0x0000000000000008  0x0000000000000010  "
                         "0x0000000000000018\n\n";

    PrintMessage(MessageType::INFO_MESSAGE, header);
    PrintMessage(MessageType::INFO_MESSAGE, "\n");

    size_t nbr = size / 0x20;
    uint32_t remain = size % 0x20;

    for (size_t i = 0; i < nbr; i++)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(i * 0x20) << "  ";
        for (uint32_t j = 0; j < 0x20; j += 8)
        {
            uint64_t value = (*(data + (i * 0x20) + j)) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 1)))) << 8)  | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 2)))) << 16) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 3)))) << 24) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 4)))) << 32) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 5)))) << 40) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 6)))) << 48) | \
                             ((static_cast<uint64_t>((*(data + (i * 0x20) + j + 7)))) << 56);
            stream << "0x" << std::setw(16) << static_cast<uint64_t>(value) << "  ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }

    if (remain)
    {
        std::stringstream stream;
        stream << std::hex << std::setfill ('0');

        stream << "0x" << std::setw(8) << static_cast<uint32_t>(0x20 * nbr) << "  ";
        for (uint32_t j = 0; j < remain; j += 8)
        {
            uint64_t value = (*(data + (nbr * 0x20) + j));
            if ((j + 1) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 1)))) << 8);
            if ((j + 2) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 2)))) << 16);
            if ((j + 3) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 3)))) << 24);
            if ((j + 4) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 4)))) << 32);
            if ((j + 5) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 5)))) << 40);
            if ((j + 6) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 6)))) << 48);
            if ((j + 7) < remain)
                value |= ((static_cast<uint64_t>((*(data + (nbr * 0x20) + j + 7)))) << 56);

            stream << "0x" << std::setw(16) << static_cast<uint64_t>(value) << "  ";
        }
        PrintMessage(MessageType::INFO_MESSAGE, stream.str());
    }
}
