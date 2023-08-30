cmake_minimum_required(VERSION 3.26)
project(untitled4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/denis/CLionProjects/TestTask/cmake-build-debug/lib/curl-8.2.1/include")


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)



add_executable(untitled4 main.cpp
        lib/Api_loader.cpp
        lib/Api_loader.h
        lib/WorkJson.cpp
        lib/WorkJson.h)
target_link_libraries(untitled4
        Qt5::Core


)






