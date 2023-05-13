//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Keyboard Module - Developed by Robert Fudge, 2023

//Header file include
#include "../include/Keyboard.hpp"

//SDL include for keyboard processing
#include <SDL2/SDL.h>

//Keyboard constructor
Keyboard::Keyboard() {
    //Initialize SDL_EVENTS for keyboard input processing
    if (SDL_Init(SDL_INIT_EVENTS) == 0) {
        isActive = true;
    }

    else {
        isActive = false;
    }
}

//Keyboard destructor
Keyboard::~Keyboard() {

}

//Keyboard input handling function
void Keyboard::handleInput() {
    SDL_Event event;
    std::string msg = "";

    //Poll
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            msg += SDL_GetKeyName(event.key.keysym.sym);
        }
    }
    message = msg;
}

//Keyboard observer attaching function
void Keyboard::attach(Observer* ob) {
    observerList.push_back(ob);
}

//Keyboard observer detaching function
void Keyboard::detach(Observer* ob) {
    observerList.remove(ob);
}

//
void Keyboard::notify() {
    std::list<Observer*>::iterator iterator = observerList.begin();
    while(iterator != observerList.end()) {
        (*iterator)->update(message);
        ++iterator;
    }
}