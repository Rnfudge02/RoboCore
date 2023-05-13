//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore File Module - Developed by Robert Fudge, 2023

//File.hpp include guard
#ifndef __FILE_HPP__
#define __FILE_HPP__

//Includes needed for file access and formatting
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>

//OpenCV include
#include <opencv2/opencv.hpp>

//File class
class File {
public:
    //Public Methods

    //Constructor and destructor
    File(std::string fileName);
    ~File();

    //Logging fucntion for storing strings in log files with timestamps
    void log(std::string text);

    //Function returning a string of the current directories contents
    std::string getDirData();

    //Function responsible for saving cv::Mat's as .png images
    bool saveImage(cv::Mat frame);

protected:
    //Ofstream object to handle file output
    std::ofstream fileStream;

private:

};

#endif  //End File.hpp