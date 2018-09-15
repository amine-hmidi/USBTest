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
#include <string>
#include <istream>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <climits>

/* C Includes */

/* User Includes */
#include "cxxopts.hpp"
#include "usb_test_cli.h"


std::string USBTestCli::version = "0.1.0";


/* ********************************************************************************************** */
/* ******************************** Class Constructor/Destructor ******************************** */
/* ********************************************************************************************** */
/**
 * @brief USBTestCli::USBTestCli
 * @param argv
 */
USBTestCli::USBTestCli(int &, char **&argv)
{
    /* Copy the apllication path */
    this->app_path = new(std::nothrow) char[strlen(argv[0]) + 1];
    if (!this->app_path)
    {
        std::cout << "Error: Unable to initialize USBTest CLI" << std::endl;
        this->app_path = nullptr;
        is_ok = false;
        return;
    }
    std::memset(this->app_path, 0x00, strlen(argv[0]) + 1);
    std::memcpy(this->app_path, argv[0], strlen(argv[0]));

    /* Init Cli Parser */
    options = new(std::nothrow) cxxopts::Options(this->app_path, " - example command line options");
    if (!options)
    {
        std::cout << "Error: Unable to initialize USBTest CLI" << std::endl;
        this->options = nullptr;
        is_ok = false;
        return;
    }
    options->positional_help("[optional args]").show_positional_help();

    /* Init CLI options */
    InitApplicationCommands();

#if defined (STANDARD_USB) || defined (USB_IN_DFU_MODE) || defined (DFU_ST_EXTENSION)
    InitUSBCommands();
#endif

#if defined (USB_IN_DFU_MODE) || defined (DFU_ST_EXTENSION)
    InitStdDFUCommands();
#endif

#if defined (DFU_ST_EXTENSION)
    InitDFUSeCommands();
#endif

    is_ok = true;
}


/**
 * @brief USBTestCli::~USBTestCli
 */
USBTestCli::~USBTestCli()
{
    /* delete app apth */
    if (this->app_path)
    {
        delete[] this->app_path;
        this->app_path = nullptr;
    }

    /* delete previous commands */
    for(int i = 1; i < argument_nbr; i++)
        delete[] arguments[i];

    delete[] arguments;
    arguments = nullptr;
    argument_nbr = 0x00;

    /* delete cli parser */
    if (this->options)
    {
        delete this->options;
        this->options = nullptr;
    }

    /* close and delete usb device */
    if (this->usb_device)
    {
        delete this->usb_device;
        this->usb_device = nullptr;
    }
}


/* ********************************************************************************************** */
/* ***************************** Parsing and executing cli options ****************************** */
/* ********************************************************************************************** */
/**
 * @brief USBTestCli::execute
 * An infinite loop requesting for new commands to be executed
 * @return
 */
int USBTestCli::execute()
{
    for(;;)
    {
        /* delete previous commands */
        for(int i = 1; i < argument_nbr; i++)
            delete[] arguments[i];

        delete[] arguments;
        arguments = nullptr;
        argument_nbr = 0x00;

        /* Get the user's input */
        std::string input;
        std::cout << "\n";
        std::cout << ">> ";
        std::getline(std::cin, input);

        std::istringstream iss(input);
        std::vector<std::string> cli_options(std::istream_iterator<std::string>{iss},\
                                             std::istream_iterator<std::string>());

        /* check the nbr of arguments */
        if (cli_options.size() > 256)
        {
            std::cout << "Error: Unable to Parse CLI, too many arguments\n";
            continue;
        }

        /* check if it was an white space carac */
        if (!cli_options.size())
            break;

        /* get the new commands */
        argument_nbr = (cli_options.size() + 1) & INT_MAX;;
        arguments = new(std::nothrow) char*[argument_nbr];
        if(!arguments)
        {
            std::cout << "Error: Unable to Parse CLI, Memory allocation error\n";
            argument_nbr = 0x00;
            continue;
        }

        /* get the app path */
        arguments[0] = app_path;

        /* get the rest of the arguments */
        for (int i = 1; i < argument_nbr; i++)
        {
            int string_size = (cli_options.at(static_cast<size_t>(i - 1)).size() + 1) & INT_MAX;
            arguments[i] = new(std::nothrow) char[string_size];
            if (!arguments[i])
            {
                std::cout << "Error: Unable to Parse CLI, Memory allocation error\n";
                for(int j = 1; j < i; j++)
                    delete[] arguments[j];

                delete[] arguments;
                argument_nbr = 0x00;
                break ;
            }
            std::memset(arguments[i], 0x00, (cli_options.at(static_cast<size_t>(i - 1)).size() + 1)\
                        & INT_MAX);
            std::memcpy(arguments[i], cli_options.at(static_cast<size_t>(i - 1)).c_str(), \
                        cli_options.at(static_cast<size_t>(i - 1)).size() + 1);
        }

        /* parse the options list */
        try {
            auto result = options->parse(this->argument_nbr, this->arguments);

            /* check exit cmd */
            if (result.count("exit"))
                break;

            /* Check common commands */
            ParseCommonCmds(result);

#if defined (STANDARD_USB)
            ParseUSBCmds(result);
#endif

        } catch (std::exception &e) {
            std::cout << "Error: " << e.what() << "\n";;
        }
    }

    return 0;
}
