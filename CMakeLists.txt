cmake_minimum_required(VERSION 3.5)
project(4122_Project)

set(CMAKE_CXX_STANDARD 11)


add_executable(4122_Project main.cpp image_processing.h extracter.h search.h jsoncpp.cpp)

target_link_libraries(4122_Project lept tesseract jsoncpp curl)


