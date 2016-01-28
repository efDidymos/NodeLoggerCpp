# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/CLang/LLVM-Linux
TARGET = Server
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets network sql
SOURCES += Initialize.cpp Server.cpp Thread.cpp main.cpp
HEADERS += Initialize.h Server.h Thread.h
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/CLang/LLVM-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = clang
QMAKE_CXX = clang++
DEFINES += DEBUG 
INCLUDEPATH += . 
LIBS += `cppunit-config --libs`  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++14
}
CONFIG += c++14
