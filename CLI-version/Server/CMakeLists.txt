cmake_minimum_required(VERSION 3.4)     # Version boundled with Clion
#cmake_minimum_required(VERSION 2.8)    # Version from Ubuntu 14.04 repository

project(Server)

# Allowing using MOC from Qt framework before compile
set(CMAKE_AUTOMOC ON)

# Path to download external Qt framework
set(CMAKE_PREFIX_PATH "~/Qt/5.5/gcc_64")

#add_definitions(-DDEBUG)   # Macro

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    Initialize.cpp
    Initialize.h
    main.cpp
    Server.cpp
    Server.h
    Thread.cpp
    Thread.h)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network Sql)

add_executable(Server ${SOURCE_FILES})

target_link_libraries(Server Qt5::Core Qt5::Widgets Qt5::Network Qt5::Sql)
