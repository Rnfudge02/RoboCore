//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore UART Module - Developed by Robert Fudge, 2023

//
#include "../include/UARTController.hpp"

//
#include <unistd.h>
#include <fcntl.h>
//#include <sys/ioctl.h>

//UARTController constructor
UARTController::UARTController() {
    file = new File("UARTController");

    initMessages();

    std::cout << UARTCONTROLLER_CONSTRUCTING << std::endl;
    file->log(UARTCONTROLLER_CONSTRUCTING);

    //Open the device
    device = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);

    //Get the current serial port settings
    tcgetattr(device, &tOptions);

    //Save previous serial port settings
    tcgetattr(device, &tPrevOptions);

    //Set the input and output baud rate
    cfsetispeed(&tOptions, B57600);
    cfsetospeed(&tOptions, B57600);

    //Set flags
    tOptions.c_cflag &= ~PARENB;
    tOptions.c_cflag &= ~CSTOPB;
    tOptions.c_cflag &= ~CSIZE;
    tOptions.c_cflag |= CS8;

    //Set cannonical mode
    tOptions.c_cflag |= ICANON;

    //Write the changes to the serial port
    tcsetattr(device, TCSANOW, &tOptions);

    std::cout << UARTCONTROLLER_CONSTRUCTED << std::endl;
    file->log(UARTCONTROLLER_CONSTRUCTED);
}

//
void UARTController::w(const char* data) {
    int bytesWritten = write(device, writeBuffer, sizeof(writeBuffer)/sizeof(char));
}

//
std::string UARTController::r() {
    int bytesRead = read(device, readBuffer, sizeof(readBuffer)/sizeof(char));

    std::string temp(readBuffer);

    return temp;
}

void UARTController::clearBuffers() {
    for (int i = 0; i < sizeof(readBuffer)/sizeof(char); i++) {
        readBuffer[i] = 0;
    }

    for (int i = 0; i < sizeof(writeBuffer)/sizeof(char); i++) {
        writeBuffer[i] = 0;
    }
}


//UARTController Destructor
UARTController::~UARTController() {
    //Restore old settings
    tcsetattr(device, TCSANOW, &tPrevOptions);

    //Close the connection
    close(device);
}


void UARTController::initMessages() {
    UARTCONTROLLER_CONSTRUCTING = "Info: UARTController constructor called";
    UARTCONTROLLER_CONSTRUCTED = "Info: UARTController constructor successful";
}