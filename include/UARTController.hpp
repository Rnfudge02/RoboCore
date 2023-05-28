//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore UART Module - Developed by Robert Fudge, 2023

//UARTController include guard
#ifndef __UART_CONTROLLER__
#define __UART_CONTROLLER__

//Include termios.h to use termios struct for holding serial configuration
#include <termios.h>
#include <string>

#include "File.hpp"

//UARTController class
class UARTController {
public:
    UARTController();
    ~UARTController();

    void w(const char* data);
    std::string r();

    void clearBuffers();

protected:
    File* file;

    std::string UARTCONTROLLER_CONSTRUCTING;
    std::string UARTCONTROLLER_CONSTRUCTED;

    std::string UARTCONTROLLER_WRITE_FAILED;
    std::string UARTCONTROLLER_READ_FAILED;

    std::string UARTCONTROLLER_DESTRUCTING;
    std::string UARTCONTROLLER_DESTRUCTED;

    int device;
    struct termios tOptions, tPrevOptions;
    char readBuffer[8];
    char writeBuffer[8];

    void initMessages();

private:

};

#endif  //End UARTController.hpp