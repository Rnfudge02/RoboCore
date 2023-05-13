//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//RoboCore Filter Module - Developed by Robert Fudge, 2023

//Header file include
#include "../include/Filter.hpp"

//Standard includes
#include <iostream>
#include <vector>

//Filter constructor
Filter::Filter() {

}

//Filter destructor
Filter::~Filter() {

}

//Function to remove color from image
cv::Mat Filter::grayScale(cv::Mat image, bool drawingToScreen) {
    cv::Mat tempImage, tempImage2;

    cv::cvtColor(image, tempImage, cv::COLOR_BGRA2GRAY);

    if (drawingToScreen) {
        std::vector<cv::Mat> channels;

        channels.push_back(tempImage);
        channels.push_back(tempImage);
        channels.push_back(tempImage);
        cv::merge(channels, tempImage2);
    }

    else {
        tempImage2 = tempImage;
    }

    return tempImage2;
}

//Function to blur image
cv::Mat Filter::blur(cv::Mat image, int kSize) {
    cv::Mat tempImage;

    cv::blur(image, tempImage, cv::Size(kSize, kSize));

    return tempImage;
}

//Function to apply a gaussian blur to the image
cv::Mat Filter::gaussianBlur(cv::Mat image, int kSize) {
    cv::Mat tempImage;

    cv::GaussianBlur(image, tempImage, cv::Size(kSize, kSize), 0, 0);

    return tempImage;
}

//Function to apply a median blur to the image
cv::Mat Filter::medianBlur(cv::Mat image, int kSize) {
    cv::Mat tempImage;

    cv::medianBlur(image, tempImage, kSize);

    return tempImage;
}

//Function to sharpen the image
cv::Mat Filter::sharpen(cv::Mat image, cv::Mat kernel) {
    cv::Mat tempImage;

    cv::filter2D(image, tempImage, -1, kernel, cv::Point(-1, -1), 0, cv::BORDER_DEFAULT);

    return tempImage;
}

//Function to perform bilateral filtering on the image
cv::Mat Filter::filterBilateral(cv::Mat image) {
    cv::Mat tempImage;

    cv::bilateralFilter(image, tempImage, 9, 75, 75);

    return tempImage;
}