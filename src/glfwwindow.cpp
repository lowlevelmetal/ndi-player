/*
 * ndi-player
 * glfwwindow.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Local includes
#include "glfwwindow.hpp"

namespace Window {

    GLFWWindow::GLFWWindow(std::string window_name, int width, int height) : GLFW() {
        // Check if GLFW() had an error
        if(GetLastError() != GlfwErrorCode::NoError) {
            ERROR("Cannot create GLFW window with context error");
            return;
        }

        // Create window
        if(!(m_glfw_window = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr))) {
            err = GlfwErrorCode::CreateWindow;
            ERROR("%s", GlfwErrorStr(err).c_str());
        }
    }

    GLFWWindow::~GLFWWindow() {
        CloseWindow();
    }

    GlfwErrorCode GLFWWindow::MakeGLContextCurrent() {
        if(!m_glfw_window)
            return (err = GlfwErrorCode::WindowUninitialized);
        
        glfwMakeContextCurrent(m_glfw_window);
        return GlfwErrorCode::NoError;
    }

    GlfwErrorCode GLFWWindow::SetDimensions(int width, int height) {
        if(!m_glfw_window)
            return (err = GlfwErrorCode::WindowUninitialized);

        glfwSetWindowSize(m_glfw_window, width, height);
        return GlfwErrorCode::NoError;
    }

    GlfwErrorCode GLFWWindow::PollEvents() {
        if(MakeGLContextCurrent() != GlfwErrorCode::NoError)
            return GetLastError();

        if(glfwWindowShouldClose(m_glfw_window)) {
            CloseWindow();
            return GlfwErrorCode::WindowClosed;
        }

        glfwPollEvents();

        return GlfwErrorCode::NoError;
    }

    void GLFWWindow::CloseWindow() {
        if(m_glfw_window)
            glfwDestroyWindow(m_glfw_window);

        m_glfw_window = nullptr;
    }

}