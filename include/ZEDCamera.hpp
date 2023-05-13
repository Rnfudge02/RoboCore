//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore ZEDCamera Module - Developed by Robert Fudge, 2023

//ZEDCamera.hpp include guard
#ifndef __ZEDCAMERA_HPP__
#define __ZEDCAMERA_HPP__

//
#include "../include/CameraInterface.hpp"

//Stereolabs camera include
#include <sl/Camera.hpp>

//ZEDCamera class
class ZEDCamera : protected CameraInterface {
public:
    ZEDCamera();
    ~ZEDCamera();

    sl::Mat getZEDMat();
    virtual cv::Mat getMat();
    virtual void saveMat() override;

    sl::Mat slMat;
    cv::Mat cvMat;

protected:
    sl::Camera zedCamera;

    sl::InitParameters initParams;

    std::string ZEDCAMERA_CONSTRUCTING;
    std::string ZEDCAMERA_CONSTRUCTED;

    std::string ZED_CAMERA_INITIALIZING;
    std::string ZED_CAMERA_INIT_SUCCESSFUL;
    std::string ZED_CAMERA_INIT_NOT_SUCCESSFUL;

    std::string ZEDCAMERA_GETFRAME_NOT_SUCCESSFUL;

    std::string ZEDCAMERA_DESTRUCTING;
    std::string ZEDCAMERA_DESTRUCTED;

    virtual void initMessages() override;

    long errorCount;

    void update();
    cv::Mat slMat2cvMat(sl::Mat& input);
    int getOCVType(sl::MAT_TYPE type);


private:

};

#endif