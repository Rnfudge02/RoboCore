//Copyright (c) 2023, Robert Fudge
//All rights reserved.
//
//This source code is licensed under the BSD-style license found in the
//LICENSE file in the root directory of this source tree. 

//

#include "../include/ZEDCamera.hpp"

sl::Resolution res(1920, 1080);

sl::Mat temp(res, sl::MAT_TYPE::U8_C4);

ZEDCamera::ZEDCamera() {
    file = new File("ZEDCamera");
    initMessages();

    std::cout << ZEDCAMERA_CONSTRUCTING << std::endl;
    file->log(ZEDCAMERA_CONSTRUCTING);

    initParams.camera_resolution = sl::RESOLUTION::HD1080;
    initParams.depth_mode = sl::DEPTH_MODE::ULTRA;
    initParams.coordinate_units = sl::UNIT::METER;

    std::cout << ZED_CAMERA_INITIALIZING << std::endl;
    file->log(ZED_CAMERA_INITIALIZING);

    sl::ERROR_CODE errorCode = zedCamera.open(initParams);

    if (errorCode != sl::ERROR_CODE::SUCCESS) {
        std::cout << ZED_CAMERA_INIT_NOT_SUCCESSFUL << std::endl;
        file->log(ZED_CAMERA_INIT_NOT_SUCCESSFUL);

        std::cout << sl::toString(errorCode);

        isRunning = false;
    }

    else {
        std::cout << ZED_CAMERA_INIT_SUCCESSFUL << std::endl;
        file->log(ZED_CAMERA_INIT_SUCCESSFUL);

        slMat = temp;
        cvMat = slMat2cvMat(slMat);

        std::cout << ZEDCAMERA_CONSTRUCTED << std::endl;
        file->log(ZEDCAMERA_CONSTRUCTED);

        isRunning = true;
    }
}

ZEDCamera::~ZEDCamera() {
    std::cout << ZEDCAMERA_DESTRUCTING << std::endl;
    file->log(ZEDCAMERA_DESTRUCTING);

    zedCamera.close();

    std::cout << ZEDCAMERA_DESTRUCTED << std::endl;
    file->log(ZEDCAMERA_DESTRUCTED);
}

sl::Mat ZEDCamera::getZEDMat() {
    update();
    return slMat;
}

cv::Mat ZEDCamera::getMat() {
    update();
    return cvMat;
}

void ZEDCamera::saveMat() {

}

void ZEDCamera::update() {
    if (isRunning && zedCamera.grab() == sl::ERROR_CODE::SUCCESS) {
        if (sl::ERROR_CODE::SUCCESS != zedCamera.retrieveImage(slMat, sl::VIEW::LEFT)) {
            
            errorCount += 1;

            if (errorCount % 30) {
                std::cout << ZEDCAMERA_GETFRAME_NOT_SUCCESSFUL << std::endl;
                file->log(ZEDCAMERA_GETFRAME_NOT_SUCCESSFUL);
            }
        }
    }
}

cv::Mat ZEDCamera::slMat2cvMat(sl::Mat& matrix) {
    return cv::Mat(matrix.getHeight(), matrix.getWidth(), getOCVType(matrix.getDataType()), matrix.getPtr<sl::uchar1>(sl::MEM::CPU), matrix.getStepBytes(sl::MEM::CPU));
}

int ZEDCamera::getOCVType(sl::MAT_TYPE type) {
    int cvType = -1;
    switch (type) {
        case sl::MAT_TYPE::F32_C1:
            cvType = CV_32FC1;
            break;

        case sl::MAT_TYPE::F32_C2:
            cvType = CV_32FC2;
            break;

        case sl::MAT_TYPE::F32_C3:
            cvType = CV_32FC3;
            break;

        case sl::MAT_TYPE::F32_C4:
            cvType = CV_32FC4;
            break;

        case sl::MAT_TYPE::U8_C1:
            cvType = CV_8UC1;
            break;

        case sl::MAT_TYPE::U8_C2:
            cvType = CV_8UC2;
            break;

        case sl::MAT_TYPE::U8_C3:
            cvType = CV_8UC3;
            break;

        case sl::MAT_TYPE::U8_C4:
            cvType = CV_8UC4;
            break;

        default:
            break;
    }

    return cvType;
}

void ZEDCamera::initMessages() {
    ZEDCAMERA_CONSTRUCTING = "Info: Constructing ZEDCamera";
    ZEDCAMERA_CONSTRUCTED = "Info: ZEDCamera constructed successfully";

    ZED_CAMERA_INITIALIZING = "Info: Initializing ZED Camera";
    ZED_CAMERA_INIT_SUCCESSFUL = "Info: ZED camera Successfully initialized";
    ZED_CAMERA_INIT_NOT_SUCCESSFUL = "Error (NON-FATAL): ZED camera could not be initialized";

    ZEDCAMERA_GETFRAME_NOT_SUCCESSFUL = "Error (NON-FATAL): Couldn't retrieve frame from ZED camera";

    ZEDCAMERA_DESTRUCTING = "Info: Destroying ZEDCamera";
    ZEDCAMERA_DESTRUCTED = "Info: ZEDCamera destroyed";
}