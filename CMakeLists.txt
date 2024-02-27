cmake_minimum_required(VERSION 3.0)

project(NDIPlayer)

# Set debug flags
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -D_DEBUG")

# Set CMAKE module include directory
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Force compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# Use GLVND instead of legacy opengl
set(OpenGL_GL_PREFERENCE "GLVND")

# Find glfw package
find_package(GLFW3 REQUIRED)

# Find glew package
find_package(GLEW REQUIRED)

# Find OpenGL package
find_package(OpenGL REQUIRED)

# Find NDI SDK
find_package(NDISDK REQUIRED)

# Setup includes
include_directories(${GLFW3_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${NDI_INCLUDE_DIR})

# Define sources
set(SOURCES
    src/ndi-player.cpp
    src/glfw.cpp
    src/glfwerror.cpp
    src/glfwwindow.cpp
    src/ndi.cpp
    src/ndireciever.cpp
    src/glvideorenderer.cpp
    src/glew.cpp
    src/averror.cpp
    src/framebuffer.cpp)

# Define executable
add_executable(ndiplayer ${SOURCES})

# Add libraries
target_link_libraries(ndiplayer ${GLFW3_LIBRARIES} ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} ${NDI_LIB})