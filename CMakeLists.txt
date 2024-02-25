cmake_minimum_required(VERSION 3.0)

project(NDIPlayer)

# Set CMAKE module include directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Force compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Find glfw package
find_package(GLFW3 REQUIRED)

# Setup includes
include_directories(${GLFW3_INCLUDE_DIRS})

# Define sources
set(SOURCES
    src/ndi-player.cpp)

# Define executable
add_executable(ndiplayer ${SOURCES})

# Add libraries
target_link_libraries(ndiplayer ${GLFW3_LIBRARIES})