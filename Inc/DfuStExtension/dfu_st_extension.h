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


#if defined (USB_DFU_STEXTENSION)

#ifndef DFU_STEXTENSION_H
#define DFU_STEXTENSION_H

/* C++ Includes */

/* C Includes */

/* User Includes */
#include "dfu_class.h"


class DFUSE : public DFUClass
{
public:

    /* ****************************************************************************************** */
    /* ******************************* Class Constructor/Destructor ***************************** */
    /* ****************************************************************************************** */
    DFUSE();
    virtual ~DFUSE();

    /* ****************************************************************************************** */
    /* ************************** Device Handling/Discovering Functions ************************* */
    /* ****************************************************************************************** */
    virtual int8_t OpenDevice();
    virtual int8_t CloseDevice();
    virtual int8_t ReOpenDevice();

    /* ****************************************************************************************** */
    /* ************************************** DFUSE Requests ************************************ */
    /* ****************************************************************************************** */
    int8_t DfuseGetCommand(uint8_t *data, uint16_t length);
    int8_t DfuSeSetAddress(uint32_t address);
    int8_t DfuSeEraseSector(uint32_t address);
    int8_t DfuSeMassErase();
    int8_t DfuSeReadUnprotect();


};

#endif

#endif
