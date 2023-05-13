//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore OCVCamera Module - Developed by Robert Fudge, 2023

//OCVCamera.hpp include guard
#ifndef __OCVCAMERA_HPP__
#define __OCVCAMERA_HPP__

//Camera interface include
#include "../include/CameraInterface.hpp"

//Observer include
#include "../include/Observer.hpp"

//Camera class
class OCVCamera : public Observer, public CameraInterface {
public:
    OCVCamera(int deviceID);
    ~OCVCamera();

    virtual void update(const std::string &message) override;

    virtual cv::Mat getMat() override;

    virtual void saveMat() override;

protected:
    //Protected members

    //String messages
    std::string CAMERA_CONSTRUCTING;
    std::string CAMERA_CONSTRUCTED;

    std::string OPENCV_VIDEOCAPTURE_INIT;
    std::string OPENCV_VIDEOCAPTURE_INIT_SUCCESSFUL;
    std::string OPENCV_VIDEOCAPTURE_INIT_NOT_SUCCESSFUL;

    std::string CAMERA_GETFRAME_NOT_SUCCESSFUL;

    std::string CAMERA_SAVE_NOT_SUCCESSFUL;

    std::string CAMERA_DESTRUCTING;
    std::string CAMERA_DESTRUCTED;

    //OpenCV VideoCpature object
    cv::VideoCapture* camFeed;

    //Camera dimensions
    double cWidth;
    double cHeight;

    //Camera Status
    int cameraID;

    //Protected methods
    virtual void initMessages() override;

private:

};

#endif  //End Camera.hpp