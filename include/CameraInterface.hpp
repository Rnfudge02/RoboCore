//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Camera Interface - Developed by Robert Fudge, 2023

//CameraInterface.hpp Include Guard
#ifndef __CAMERA_INTERFACE_HPP__
#define __CAMERA_INTERFACE_HPP__

#include <opencv2/opencv.hpp>

#include "../include/File.hpp"

//
class CameraInterface {
public:
    virtual ~CameraInterface() { };

    virtual cv::Mat getMat() = 0;
    virtual void saveMat() = 0;

    virtual bool getStatus() {
        return isRunning;
    }

protected:
    File* file;
    
    bool isRunning;

    virtual void initMessages() = 0;

private:

};

#endif