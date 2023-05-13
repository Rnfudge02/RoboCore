#CMakeLists.txt for RoboCore V1.1.0

#Set required CMake version
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Set project name
project(RoboCore)

#Set cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#Get all source files
file(GLOB SOURCES "src/*.cpp")

#Find Required Packages
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

find_package(ZED 4 REQUIRED)
find_package(OpenCV REQUIRED)
find_package(CUDA 12 REQUIRED)

add_definitions(-Wall -Og -std=c++17)

#Set appropriate include directories
include_directories(include)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
include_directories(${SDL2_TTF_INCLUDE_DIRS})

include_directories(${OpenCV_INCLUDE_DIRS})

include_directories(${ZED_INCLUDE_DIRS})
include_directories(${CUDA_INCLUDE_DIRS})

#Executable
add_executable(RoboCore ${SOURCES})

#Perform Linking
target_link_libraries(RoboCore ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARY} ${SDL2_TTF_LIBRARY} ${OpenCV_LIBS} ${ZED_LIBRARIES} ${CUDA_CUDA_LIBRARY} ${CUDA_CUDART_LIBRARY})