/*
 * ndi-player
 * glfwerror.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <string>

namespace Window {
    enum class GlfwErrorCode {
        NoError,
        GlfwInit,
        CreateWindow,
        WindowUninitialized,
        WindowClosed,
        WindowInitialized
    };

    std::string GlfwErrorStr(GlfwErrorCode &err);
} // namespace Window