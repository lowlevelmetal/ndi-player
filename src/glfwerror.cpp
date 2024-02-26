/*
 * ndi-player
 * glfwerror.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// local includes
#include "glfwerror.hpp"

namespace Window {
    std::string GlfwErrorStr(GlfwErrorCode &err) {
        switch(err) {
            case GlfwErrorCode::NoError:
                return std::string("No glfw error");
            case GlfwErrorCode::GlfwInit:
                return std::string("Failed to initialize GLFW");
            case GlfwErrorCode::CreateWindow:
                return std::string("Failed to create window");
            case GlfwErrorCode::WindowUninitialized:
                return std::string("Tried to preform operation on uninitialized window");
            case GlfwErrorCode::WindowClosed:
                return std::string("Window is closed");
        }

        return std::string("Invalid GLFW error code");
    }
} // namespace Window