cmake_minimum_required(VERSION 3.0)
project(TnHelpers CXX)

include_directories(Inc/TnHelpers)

set(PFX "Tn")

add_library(${PFX}Helpers INTERFACE)
target_include_directories(${PFX}Helpers INTERFACE Inc/)

add_library(${PFX}Exception Src/Exception.cpp)
target_link_libraries(${PFX}Exception ${PFX}Helpers)

add_library(${PFX}FileDescriptor Src/FileDescriptor.cpp)
target_link_libraries(${PFX}FileDescriptor PUBLIC ${PFX}Exception)

add_library(${PFX}PThread Src/PThread.cpp)
target_link_libraries(${PFX}PThread PUBLIC pthread ${PFX}Exception)

add_library(${PFX}Logger Src/Logger.cpp)
target_link_libraries(${PFX}Logger PUBLIC ${PFX}PThread)

add_library(${PFX}Selector Src/Selector.cpp)
target_link_libraries(${PFX}Selector PUBLIC ${PFX}Exception)

add_library(${PFX}Files Src/Files.cpp)
target_link_libraries(${PFX}Files PUBLIC ${PFX}Exception)

add_library(${PFX}Pipe Src/Pipe.cpp)
target_link_libraries(${PFX}Pipe PUBLIC ${PFX}Exception ${PFX}FileDescriptor)
