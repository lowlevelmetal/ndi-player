/*
 * ndi-player
 * glfwwindow.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <string>

// Local includes
#include "glfw.hpp"
#include "macro.hpp"

namespace Window {

    class GLFWWindow : public GLFW {
        public:
            GLFWWindow(std::string window_name = "NDI Player", int width = 640, int height = 480);
            ~GLFWWindow();

            GlfwErrorCode MakeGLContextCurrent();
            GlfwErrorCode SetDimensions(int width, int height);
            GlfwErrorCode PollEvents();
            void CloseWindow();
            GlfwErrorCode OpenWindow(std::string &window_name, int width, int height);

        private:
            GLFWwindow *m_glfw_window = nullptr;

    };

} // namespace Window