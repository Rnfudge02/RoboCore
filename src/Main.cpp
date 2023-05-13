//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//Include modules
#include "../include/ZEDCamera.hpp"
#include "../include/Display.hpp"
#include "../include/Keyboard.hpp"

//Object instantiation
Keyboard* keyboard;

ZEDCamera* zedCamera1;
Display* display;

//Main Function
int main() {
    keyboard = new Keyboard();

    zedCamera1 = new ZEDCamera();

    /*
    cv::namedWindow("WINDOW");

    char key = ' ';

    while(key != 'q') {
        cv::Mat frame = zedCamera1->getMat();
        cv::imshow("WINDOW", frame);
        key = cv::waitKey(10);
    }

    */
    
    display = new Display(0, "DejaVuSans.ttf");

    keyboard->attach(display);

    while (display->getStatus()) {
        keyboard->handleInput();
        keyboard->notify();

        display->handleQuit();

        cv::Mat frame = zedCamera1->getMat();

        SDL_Texture* tex = display->createTextureFromText("HELLO", display->BLUE);

        display->passToRenderer(frame, 1);
        display->passToRenderer(tex, 2);
        display->renderFolder(display->GREEN);

        display->drawGUI();
    }

    keyboard->detach(display);

    delete display;
    
    delete zedCamera1;

    delete keyboard;

    //Return with no errors (0)
    return 0;
}