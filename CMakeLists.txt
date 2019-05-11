cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(QtCmakePro)

add_definitions(-std=c++11)
set(CMAKE_CXX_FLAGS "-std=c++11")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)
set(QT_LIBRARIES Qt5::Widgets Qt5::Network)

add_subdirectory(libCore)
add_subdirectory(mainProject)

