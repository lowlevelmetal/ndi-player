/*
 * ndi-player
 * ndi-player.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Standard includes
#include <cstdlib>

// local includes
#include "glfwwindow.hpp"


int main(int, char **) {
    Window::GLFWWindow window;
    if(window.GetLastError() != Window::GlfwErrorCode::NoError)
        FATAL("Failed to create window")

    Window::GlfwErrorCode ret;
    while((ret = window.PollEvents()) == Window::GlfwErrorCode::NoError);

    if(ret != Window::GlfwErrorCode::WindowClosed) {
        FATAL("%s", Window::GlfwErrorStr(ret).c_str());
    }

    return EXIT_SUCCESS;
}