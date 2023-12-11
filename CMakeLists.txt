cmake_minimum_required(VERSION 3.0)
project(TnHelpers CXX)

include_directories(Inc/)

set(PFX "Tn")

add_library(${PFX}Helpers INTERFACE)
target_include_directories(${PFX}Helpers INTERFACE .)

add_library(${PFX}Exception Src/Exception.cpp Inc/Exception.hpp)
target_link_libraries(${PFX}Exception ${PFX}Helpers)

add_library(${PFX}FileDescriptor Src/FileDescriptor.cpp Inc/FileDescriptor.hpp)
target_link_libraries(${PFX}FileDescriptor PUBLIC ${PFX}Exception)

add_library(${PFX}PThread Src/PThread.cpp Inc/PThread.hpp)
target_link_libraries(${PFX}PThread PUBLIC pthread ${PFX}Exception)

add_library(${PFX}Logger Src/Logger.cpp Inc/Logger.hpp)
target_link_libraries(${PFX}Logger PUBLIC ${PFX}PThread)

add_library(${PFX}Selector Src/Selector.cpp Inc/Selector.hpp)
target_link_libraries(${PFX}Selector PUBLIC ${PFX}Exception)

add_library(${PFX}Files Src/Files.cpp Inc/Files.hpp)
target_link_libraries(${PFX}Files PUBLIC ${PFX}Exception)

add_library(${PFX}Pipe Src/Pipe.cpp Inc/Pipe.hpp)
target_link_libraries(${PFX}Pipe PUBLIC ${PFX}Exception ${PFX}FileDescriptor)
