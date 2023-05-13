//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore File Module - Developed by Robert Fudge, 2023

//Header file include
#include "../include/File.hpp"

//Filesystem include (c++17 feature only)
#include <filesystem>

//File constructor
File::File(std::string fileName) {
    //Get current time to append to log file name
    time_t now = std::time(0);
    tm* ltm = std::localtime(&now);

    //Use ostream and put_time to get it in the correct format as a string
    std::ostringstream o;
    o << fileName << std::put_time(ltm, "-%d-%m-%Y") << ".dat";
    std::string fileString = o.str();
    
    fileStream.open(fileString, std::ios::out);
}

//File destructor
File::~File() {
    fileStream.close();
}

//Write string to log file with current time data
void File::log(std::string text) {
    //Get current time to append to log file name
    time_t now = time(0);
    tm* ltm = localtime(&now);

    //Use ostream and put_time to get it in the correct format as a string
    std::ostringstream o;
    o << "[" << std::put_time(ltm, "%d-%m-%Y %H:%M:%S") << "]| ";
    std::string timeStr = o.str();

    fileStream << timeStr << text << std::endl;
}

//Formats directory information as string and returns to caller
std::string File::getDirData() {
    //Get current working directory and convert it to a string
    std::filesystem::path cwd = std::filesystem::current_path();
    std::string cwdStr = cwd.string();

    //Create blank string for appending to later
    std::string returnString = "";

    //Use for loop to get all folders/files contained in current woring directory, convert to string, and then append them to the return string
    for (const auto & entry : std::filesystem::directory_iterator(cwdStr)) {
        std::string temp = entry.path().string();
        temp = temp.substr(cwdStr.size() + 1, temp.size() - (cwdStr.size()  + 1));

        std::string temp1;

        if (temp.find(".") == std::string::npos) {
            temp1 = "[Folder] | " + temp;
        }

        else {
            temp1 = "[File] | " + temp;
        }

        returnString += ("\n" + temp1);
    }

    return returnString;
}

//Saves cv::Mat passed in as .png image
bool File::saveImage(cv::Mat frame) {
    //Get current time to append to log file name
    time_t now = time(0);
    tm* ltm = localtime(&now);

    //Use ostream and put_time to get it in the correct format as a string
    std::ostringstream o;
    o << "" << std::put_time(ltm, "%d-%m-%Y %H:%M:%S");
    std::string timeStr = o.str();

    //Create filename string to save as
    std::string filename = "./image-" + timeStr + ".png";

    //Perform the write and save return status
    bool returnStatus = cv::imwrite(filename, frame);

    //Return the write status to caller
    return returnStatus;
}

//End File.cpp