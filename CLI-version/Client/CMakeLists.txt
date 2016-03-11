cmake_minimum_required(VERSION 3.4)     # Version boundled with Clion
#cmake_minimum_required(VERSION 2.8)    # Version from Ubuntu 14.04 repository

project(Client)

set(CMAKE_AUTOMOC ON)   # Allowing using MOC from Qt framework before compile

set(CMAKE_PREFIX_PATH "~/Qt/5.5/gcc_64")    # Path to download external Qt framework

#add_definitions(-DDEBUG)   # Macro

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
    config.json
    main.cpp
    testFile1.log
    testFile2.log
    watcher.cpp
    watcher.h)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)

add_executable(Client ${SOURCE_FILES})

target_link_libraries(Client Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)
