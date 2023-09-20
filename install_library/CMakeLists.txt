# Определение минимальной версии CMake
cmake_minimum_required(VERSION 3.23)

# Название проекта
project(install_library)



# Укажите пути к библиотекам rpmLib и Qt5Core
set(RPMLIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../external/librpm/lib64/librpm.so")
set(QT5CORE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt5/lib/libQt5Core.so.5.15.2")

add_library(rpmLib2 SHARED IMPORTED)
add_library(Qt5Core2 SHARED IMPORTED)

set_target_properties(rpmLib2 PROPERTIES IMPORTED_LOCATION ${RPMLIB_PATH})
set_target_properties(Qt5Core2 PROPERTIES IMPORTED_LOCATION ${QT5CORE_PATH})

add_library(MyLibrary SHARED
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Api_loader.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/WorkJson.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/MyLib.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Api_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/WorkJson.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/MyLib.h
)
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt5/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/librpm/include
)

link_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/Qt5/lib
        ${CMAKE_CURRENT_SOURCE_DIR}/../external/librpm/lib64
)

# Устанавливаем зависимости для MyLibrary
target_link_libraries(MyLibrary Qt5Core2 rpmLib2)

# Укажите пути для установки библиотеки MyLibrary
install(TARGETS MyLibrary DESTINATION lib)
install(FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/Api_loader.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/WorkJson.h
        ${CMAKE_CURRENT_SOURCE_DIR}/../lib/MyLib.h
        DESTINATION include)