//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Keyboard Module - Developed by Robert Fudge, 2023

//Keyboard.hpp include guard
#ifndef __KEYBOARD_HPP__
#define __KEYBOARD_HPP__

//Subject header include
#include "./Subject.hpp"

//Standard includes
#include <list>

//Keyboard class
class Keyboard : public Subject {
public:
    Keyboard();
    ~Keyboard();

    virtual void attach(Observer* ob) override;
    virtual void detach(Observer* ob) override;

    virtual void notify() override;

    void handleInput();

protected:
    std::list<Observer*> observerList;

    std::string message;

    bool isActive;

private:

};

#endif  //End Keyboard.hpp