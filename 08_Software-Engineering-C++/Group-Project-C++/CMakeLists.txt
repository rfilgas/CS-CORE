cmake_minimum_required(VERSION 3.8)

set(This Choc_Ann)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

set(Headers
    account_manager.h 
    chocann_access.h 
    interface.h 
    member_object.h 
    provider_directory.h 
    provider_object.h 
    service_recieved.h 
    service_rendered.h 
    utility.h 
)

set(Sources
    account_manager.cpp 
    chocann_access.cpp
    interface.cpp
    main.cpp
    member_object.cpp
    provider_directory.cpp 
    provider_object.cpp 
    service_recieved.cpp
    service_rendered.cpp
    utility.cpp
)

add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test);