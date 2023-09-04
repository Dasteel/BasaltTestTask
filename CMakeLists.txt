cmake_minimum_required(VERSION 3.25)
project(untitled4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(SOURCE_FILES
        lib/Api_loader.cpp
        lib/WorkJson.cpp
        lib/MyLib.cpp
)
# Создать разделяемую библиотеку
add_library(MyLibrary SHARED ${SOURCE_FILES})

# Указать пути к заголовочным файлам
target_include_directories(MyLibrary PUBLIC lib)


find_package(Qt5 COMPONENTS
        Core
        REQUIRED)



add_executable(untitled4 main.cpp
        lib/Api_loader.cpp
        lib/Api_loader.h
        lib/WorkJson.cpp
        lib/WorkJson.h
        lib/MyLib.cpp
        lib/MyLib.h
        version.h
)
# Связать библиотеку с Qt5::Core
target_link_libraries(MyLibrary Qt5::Core)
target_link_libraries(untitled4
        Qt5::Core
        MyLibrary
)








