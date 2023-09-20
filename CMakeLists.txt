# Определение минимальной версии CMake
cmake_minimum_required(VERSION 3.23)

# Название вашего проекта
project(untitled4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -fPIC -Wno-dev")



add_library(rpmLib SHARED IMPORTED)
set_target_properties(rpmLib PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/librpm/lib64/librpm.so")

add_library(Qt5Core SHARED IMPORTED)
set_target_properties(Qt5Core PROPERTIES IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/external/Qt5/lib/libQt5Core.so.5.15.2")

# Выполняем второй CMake-файл перед сборкой основного проекта
add_custom_target(run_install_library
        COMMAND ${CMAKE_MAKE_PROGRAM} -C ${CMAKE_BINARY_DIR}/install_library install
        COMMENT "Running install_library"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# Указываем директорию, где находится второй CMake-файл
add_subdirectory(install_library)

# Создаем исполняемый файл
add_executable(untitled4 main.cpp version.h)

# Устанавливаем зависимость от библиотеки и от выполнения второго CMake-файла
add_dependencies(untitled4 MyLibrary run_install_library)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/external/Qt5/include
        ${CMAKE_CURRENT_SOURCE_DIR}/external/librpm/include
)

link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/external/Qt5/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/external/librpm/lib64
)

target_link_libraries(untitled4
        MyLibrary
        Qt5Core
        rpmLib
)