//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Filter Module - Developed by Robert Fudge, 2023

//Filter.hpp include guard
#ifndef __FILTER_HPP__
#define __FILTER_HPP__

//Opencv include
#include <opencv2/opencv.hpp>

//Filter class
class Filter {
public:
    Filter();
    ~Filter();

    //Color space functions
    cv::Mat grayScale(cv::Mat image, bool drawingToScreen = false);

    //Blur functions
    cv::Mat blur(cv::Mat image, int kSize = 5);
    cv::Mat gaussianBlur(cv::Mat image, int kSize = 5);
    cv::Mat medianBlur(cv::Mat image, int kSize = 5);

    //Sharpening functions
    cv::Mat sharpen(cv::Mat image, cv::Mat kernel = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 5, -1, 0, -1, 0));
    cv::Mat filterBilateral(cv::Mat image);

protected:

private:

};

#endif  //End Filter.hpp