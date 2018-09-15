#################################################################################################
######################################### Copyright (C) #########################################
#################################################################################################
#                                                                                               #
# This file is part of USBTest Suite.                                                           #
#                                                                                               #
# USBTest Suite is free software; you can redistribute it and/or                                #
# modify it under the terms of the GNU General Public License                                   #
# as published by the Free Software Foundation; either version 2                                #
# of the License, or (at your option) any later version.                                        #
#                                                                                               #
# USBTest Suite is distributed in the hope that it will be useful,                              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                                #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                                 #
# GNU General Public License for more details.                                                  #
#                                                                                               #
# You should have received a copy of the GNU General Public License                             #
# along with USBTest Suite; if not, write to the Free Software                                  #
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.               #
#                                                                                               #
# Copyright (C) 2018  Amine Hmidi (amine.hmidi0.1@gmail.com)                                    #
#                                                                                               #
#################################################################################################


#################################################################################################
############################### PROJECT TEMPLATE/CONFIGURATION ##################################
#################################################################################################

############ TEMPLATE
TEMPLATE = app
VERSION = 0.1.0
QMAKE_TARGET_PRODUCT = USBTest
QMAKE_TARGET_COPYRIGHT = GPLv2.0
QMAKE_TARGET_DESCRIPTION = A user space application for USB testing

############ CONFIGURATION
CONFIG += console c++11
CONFIG += static
CONFIG -= app_bundle
CONFIG -= qt

#################################################################################################
################################# PROJECT OUPUT DIRECTORIES #####################################
#################################################################################################

CONFIG(debug, debug|release) {
############ DEBUG OUPUT
    DESTDIR = build/USBTest/debug
} else {
############ RELEASE OUPUT
    DESTDIR = build/USBTest/release
}


OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

win32 {
QMAKE_CLEAN += $${DESTDIR}/USBTest.exe
}

unix {
QMAKE_CLEAN += $${DESTDIR}/USBTest
}


#################################################################################################
###################################### PROJECT DEFINES ##########################################
#################################################################################################

############
DEFINES += \
    STANDARD_USB \
    #DFU_ST_EXTENSION \
    #USB_IN_DFU_MODE

#################################################################################################
############################### PROJECT SOURCE/INCLUDE FILES ####################################
#################################################################################################

############ SOURCE FILES
SOURCES += \
    ../Src/main.cpp \
    ../Src/StandardUSB/standard_usb.cpp \
    ../Src/StandardUSB/usb_standard_requests.cpp \
    ../Src/StandardUSB/usb_descriptors_requests.cpp \
    #../Src/DFU1.1/dfu_class.cpp \
    #../Src/DFU1.1/dfu_requests.cpp \
    #../Src/DFU1.1StExtension/dfu_st_extension.cpp \
    #../Src/DFU1.1StExtension/dfu_st_special_cmds.cpp \
    ../Src/CommandLineInterface/usb_test_cli_common.cpp \
    ../Src/CommandLineInterface/usb_test_cli.cpp \
    #../Src/CommandLineInterface/usb_test_cli_dfu_se.cpp \
    #../Src/CommandLineInterface/usb_test_cli_dfu.cpp \
    ../Src/CommandLineInterface/usb_test_cli_copyrights_warranty.cpp \
    #../Src/FileManager/dfu_file.cpp
    ../Src/CommandLineInterface/usb_test_cli_std_usb.cpp


############ INCLUDE FILES
HEADERS += \
    ../Inc/StandardUSB/standard_usb.h \
    #../Inc/DFU1.1/dfu_class.h \
    #../Inc/DFU1.1StExtension/dfu_st_extension.h \
    ../Inc/CommandLineInterface/usb_test_cli.h \
    #../Inc/FileManager/dfu_file.h


############ INCLUDE DIRECTORIES
INCLUDEPATH += \
    ../Inc/ \
    ../Inc/StandardUSB/ \
    #../Inc/DFU1.1/ \
    #../Inc/DFU1.1StExtension/ \
    ../Inc/CommandLineInterface/ \
    #../Inc/FileManager/


#################################################################################################
################################ PROJECT EXTERNAL LIBRARIES #####################################
#################################################################################################


############ COMMON BETWEEN LINUX AND WINDOWS
INCLUDEPATH += \
    ../ExternalLibs/cxxopts-2_0/include

win32 {
############ INCLUDE DIRECTORIES
INCLUDEPATH += \
    ../ExternalLibs/libusb-1.0.22/include/

############ LIBS(.dll, .so, .lib & .a)
LIBS += ../ExternalLibs/libusb-1.0.22/MinGW32/static/libusb-1.0.a
}

unix {
############ INCLUDE DIRECTORIES
INCLUDEPATH += \

############ LIBS(.dll, .so, .lib & .a)
LIBS += -lusb-1.0
}
