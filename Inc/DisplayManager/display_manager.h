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

#ifndef DISPLAY_MANAGER
#define DISPLAY_MANAGER

/* C++ Includes */
#include <iostream>
#include <iomanip>
#include <ios>
#include <string>

/* C Includes */

/* User Includes */


class DisplayManager
{
public:

    enum MessageType
    {
        BASIC_MESSAGE       = 0,
        INFO_MESSAGE        = 1,
        WARNING_MESSAGE     = 2,
        ERROR_MESSAGE       = 3
    };


    // delete copy and move constructors and assign operators
    DisplayManager(DisplayManager const&) = delete;             // Copy construct
    DisplayManager(DisplayManager&&) = delete;                  // Move construct
    DisplayManager& operator=(DisplayManager const&) = delete;  // Copy assign
    DisplayManager& operator=(DisplayManager &&) = delete;      // Move assign

    static DisplayManager* Instance();
    static void Destroy();

    void PrintMessage(DisplayManager::MessageType type = DisplayManager::MessageType::BASIC_MESSAGE,
                      const std::string& message= "");
    void PrintMessage(DisplayManager::MessageType type = DisplayManager::MessageType::BASIC_MESSAGE,
                      const char * message = "");
    void DisplayData8(uint8_t *data, size_t size);
    void DisplayData16(uint8_t *data, size_t size);
    void DisplayData32(uint8_t *data, size_t size);
    void DisplayData64(uint8_t *data, size_t size);

protected:

    DisplayManager() { std::ios_base::sync_with_stdio(false); }
    ~DisplayManager() {}

    static DisplayManager* display_manager;

};


#endif
