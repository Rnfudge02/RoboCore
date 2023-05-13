//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Observer Module - Developed by Robert Fudge, 2023

//Obsever.hpp include guard
#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

//Include string to permit message transfer between subject and observers
#include <string>

//Observer pure virtual class
class Observer {
public:
    //Virtual destructor to protect against undefined behavior
    virtual ~Observer() { };

    //Virtual update method that must be implemented by all inheritors
    virtual void update(const std::string &message) = 0;

protected:

private:

};

#endif  //End Observer.hpp