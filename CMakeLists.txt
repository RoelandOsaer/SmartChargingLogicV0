cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SmartCharingingLogic)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h")

# Add an executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

# Find and link the mosquitto library

message(STATUS "Mosquitto include dirs: ${MOSQUITTO_INCLUDE_DIRS}")
message(STATUS "Mosquitto libraries: ${MOSQUITTO_LIBRARIES}")

set(MOSQUITTO_INCLUDE_DIRS "libs/mosquitto/devel")

#for now, building the project gives error on this (can not open mosquitto.lib).
set(MOSQUITTO_LIBRARIES    "libs/mosquitto/devel/mosquitto.lib")

include_directories(${MOSQUITTO_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${MOSQUITTO_LIBRARIES})
