//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Subject Module - Developed by Robert Fudge, 2023

//Subject.hpp include guard
#ifndef __SUBJECT_HPP__
#define __SUBJECT_HPP__

//Observer header include
#include "./Observer.hpp"

//Subject pure virtual class
class Subject {
public:
    //Virtual destructor to protect against undefined behavior
    virtual ~Subject() { };

    //Virtual attach and detach methods that must be implemented by all inheritors
    virtual void attach(Observer* ob) = 0;
    virtual void detach(Observer* ob) = 0;


    //Virtual notify method that must be implemented by all inheritors
    virtual void notify() = 0;

protected:

private:
};

#endif