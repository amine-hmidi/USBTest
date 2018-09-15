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
#include <ios>

/* C Includes */

/* User Includes */
#include "usb_test_cli.h"





int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);

    std::cout << "\n";
    std::cout << "USBTest Suite version " << USBTestCli::Version();
    std::cout << ", Copyright (C) 2018 Amine Hmidi\n";
    std::cout << "(amine.hmidi0.1@gmail.com). USBTest Suite comes with ABSOLUTELY NO WARRANTY;\n";
    std::cout << "for details type `--show_w'. This is free software, and you are welcome\n";
    std::cout << "to redistribute it under certain conditions; type `--show_c'for details.\n";
    std::cout << "\n";

    USBTestCli cli(argc, argv);
    if(!cli.IsOk())
        return -1;

    return cli.execute();
}
