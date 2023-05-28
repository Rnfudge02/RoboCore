# RoboCore
An open-source library for easing the design of robotics projects in C++

Instructions:
- Include required modules in main.cpp and write procedural code in main.cpp
- Add preferred font to resources/fonts and pass the filename to the Display() constructor
- Call cmake-gui to generate cmake build files
- Copy resources folder to build folder
- Use 'cd build' and 'make -jX' to build the project, where X is the number of parallel jobs to execute (Use number of CPU cores your processor has)
- Call ./RoboCore to run the application

Requirements:
- LibSDL2, LibSDL2-image, and LibSDL_TTF <- use 'sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev cmake'
- nVidia CUDA V12.0 or later <- https://developer.nvidia.com/cuda-downloads
- ZSTD <- use 'sudo apt-get install zstd'
- ZED SDK V4.0 <- https://www.stereolabs.com/developers/release/

Changelogs:

V 1.2.0A Changelog

New Features:
- Partially functioning UART controller, still in debugging stages
- New build script in home directory which 

V 1.1.0 Changelog

New Features:
- Added Scripts for creating and moving data to and from Ramdisk for faster compilation
- Added scripts to add resources for SDL_image and SDL_TTF into the build directory
- Switched from Makefile to CMake to eventually make source code cross-platform compatible
- Added ZED Camera support
- Added make command to facilitate ramdisk usage, could allow for faster compilation times, looking into precompiled headers for a future release

Known Bugs:
- Keyboard should currently only be initialized when Display is also initialized, and should be destructed before Display is destructed to prevent errors, working on a fix
- Images retrieved from the ZED Camera currently will not render in the display

V 1.0.0 Changelog

New Features:
- Overloaded passToRenderer() to have an implementation for cv::Mat's as well as SDL_Texture*'s
- passToRenderer() now takes the data to be drawn first and then the frameNum, this is done to facilitate a default argument for frameNum, which will now default to 4 if not specified
- Changed access permissions on createTextureFromMat(cv::Mat) and createTextureFromText(std::string text) to allow end user to create textures easier
- Added an argument to Filter::grayScale(cv::Mat image, bool drawingToScreen) to optionally remove the recompiling of a 3 channel image for displaying to the screen, this allows the end user to retrieve a single channel image from it for further image processing
- Added dynamic resizing of SDL_Rects for terminal and file textures to prevent text blurring, done within createTextureFromText() which now also takes in arguments to specify which SDL_Rect to resize, if any
- Broke message initialization for Display and Camera into protected initMessages() functions, improving code readability
- Revised makefile to allow for debug builds (used for testing rigidity of code) and release builds (better optimization)
- Added colour options for text rendering in renderFolder and createTextureFromText
- Added pure virtual Subject and Observer headers, facilitating messaging between classes
- Added iterator pattern to keyboards implementation of Subject
- Display module now inherits from Observer, allowing for additional features to be added in the future
- Display::handleEvents() has been re-factored to abide by Observer principles
- Camera module now inherits from Observer
- Camera::saveFrame() functionality added, facilitated by Subject/Observer pattern
- Added Keyboard module, which inherits from Subject
- Added clrlogs routine to make to clear any excess log files left in main directory

Optimizations:
- Fixed renderFolder() so that it only updates when the text returned from getDirData() changes

Known Bugs:
- Keyboard should currently only be initialized when Display is also initialized, and should be destructed before Display is destructed to prevent errors, working on a fix

License:
BSD 3-Clause License

Copyright (c) 2023, Rnfudge02

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
