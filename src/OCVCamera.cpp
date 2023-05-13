//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Camera Module - Developed by Robert Fudge, 2023

//Header file include
#include "../include/OCVCamera.hpp"

//Standard includes
#include <iostream>

//Camera constructor
OCVCamera::OCVCamera(int cameraID) {
    //Set up file logging
    file = new File("OCVCamera" + std::to_string(cameraID));

    //Initialize messages for logging
    initMessages();

    //Notify user that camera constructor was called
    std::cout << CAMERA_CONSTRUCTING << std::endl;
    file->log(CAMERA_CONSTRUCTING);

    //Initialize camFeed with camera object
    camFeed = new cv::VideoCapture(cameraID);

    //Notify user that a camera is being created
    std::cout << OPENCV_VIDEOCAPTURE_INIT << std::to_string(cameraID) << std::endl;
    file->log(OPENCV_VIDEOCAPTURE_INIT + std::to_string(cameraID));

    //If after the camera has been created it is still not open, notify user that an error has occured
    if (camFeed->isOpened() == false) {
        std::cerr << OPENCV_VIDEOCAPTURE_INIT_NOT_SUCCESSFUL << std::to_string(cameraID) << std::endl;
        file->log(OPENCV_VIDEOCAPTURE_INIT_NOT_SUCCESSFUL + std::to_string(cameraID));
        isRunning = false;
    }

    //If camera is opened successfully
    else {
        //Set camera properties
        this->cameraID = cameraID;
        cWidth = camFeed->get(cv::CAP_PROP_FRAME_WIDTH);
        cHeight = camFeed->get(cv::CAP_PROP_FRAME_HEIGHT);

        //Notify user that camera initialization was successful
        std::cout << OPENCV_VIDEOCAPTURE_INIT_SUCCESSFUL << std::to_string(cameraID) << std::endl;
        file->log(OPENCV_VIDEOCAPTURE_INIT_SUCCESSFUL + std::to_string(cameraID));

        isRunning = true;
    }
}

//Camera destructor
OCVCamera::~OCVCamera() {
    //Notify user that the camera destructor has been called
    std::cout << CAMERA_DESTRUCTING << std::endl;
    file->log(CAMERA_DESTRUCTING);

    //Release the camera feed and destroy the camera object
    camFeed->release();
    delete camFeed;

    //Notify user that camera destruction was successful
    std::cout << CAMERA_DESTRUCTED << std::endl;
    file->log(CAMERA_DESTRUCTED);

    //Close file
    delete file;
}

void OCVCamera::update(const std::string &message) {
    if (message.find('S') != std::string::npos or message.find('s') != std::string::npos) {
        saveMat();
    }
}

//Function to retrieve frame from camera
cv::Mat OCVCamera::getMat() {
    cv::Mat frame;
    //If camera is running, retrieve frame and return it
    if (isRunning) {
        camFeed->read(frame);
        return frame;
    }

    //If camera is not running, notify user via std::cerr and return empty frame
    else {
        std::cerr << CAMERA_GETFRAME_NOT_SUCCESSFUL << std::to_string(cameraID) << std::endl;
        file->log(CAMERA_GETFRAME_NOT_SUCCESSFUL + std::to_string(cameraID));
        return frame; 
    }
}

void OCVCamera::saveMat() {
    cv::Mat frame = getMat();
    bool check = file->saveImage(frame);

    if (check != 0) {
        std::cerr << CAMERA_SAVE_NOT_SUCCESSFUL << std::endl;
        file->log(CAMERA_SAVE_NOT_SUCCESSFUL);
    }
}

void OCVCamera::initMessages() {
    CAMERA_CONSTRUCTING = "Info: Camera constructor called";
    CAMERA_CONSTRUCTED = "Info: Camera constructor successful";

    OPENCV_VIDEOCAPTURE_INIT = "Info: Initializing OpenCV::VideoCapture for camera ";
    OPENCV_VIDEOCAPTURE_INIT_SUCCESSFUL = "Info: Successfully intialized camera ";
    OPENCV_VIDEOCAPTURE_INIT_NOT_SUCCESSFUL = "Error (FATAL): Could not intialize camera ";

    CAMERA_GETFRAME_NOT_SUCCESSFUL = "Error (NON-FATAL): Could not retrieve frame from camera ";

    CAMERA_SAVE_NOT_SUCCESSFUL = "Error (NON-FATAL): Could not save image";

    CAMERA_DESTRUCTING = "Info: Camera destructor called";
    CAMERA_DESTRUCTED = "Info: Camera successfully destroyed\n\nEOF";
}

//End Camera.cpp