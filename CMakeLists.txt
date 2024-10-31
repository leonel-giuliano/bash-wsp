# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Define the project name, version, and language (C only)
project(bash-wsp VERSION 1.0 LANGUAGES C)

# Set the source files directory and include directory
set(SERVER_SOURCE_DIR "${CMAKE_SOURCE_DIR}/server")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")

# Add the custom debug definition
add_definitions(-D_DEBUG_ON)

# Include directories
include_directories(${INCLUDE_DIR})

# Find all .c files in the SERVER_SOURCE_DIR
file(GLOB SERVER_SOURCES "${SERVER_SOURCE_DIR}/*.c")

# Check if any source files were found
if(NOT SERVER_SOURCES)
    message(FATAL_ERROR "No source files found in ${SERVER_SOURCE_DIR}")
endif()

# Add an executable target for the server
add_executable(server ${SERVER_SOURCES})

# Link the executable with the errnum library located in LIB_DIR
target_link_libraries(server PRIVATE errnum)
target_link_directories(server PRIVATE ${LIB_DIR})

# Optionally, set build type to debug (default)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
