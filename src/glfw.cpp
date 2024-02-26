/*
 * ndi-player
 * glfw.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Local includes
#include "glfw.hpp"
#include "macro.hpp"

namespace Window {

    int GLFW::m_open_instances = 0;

    GLFW::GLFW() {
        if(!m_open_instances) {
            if(!glfwInit()) {
                err = GlfwErrorCode::GlfwInit;
                ERROR("%s", GlfwErrorStr(err).c_str());
            }
        }

        m_open_instances++;
    }

    GLFW::~GLFW() {
        m_open_instances--;

        if(!m_open_instances) {
            glfwTerminate();
        }
    }

    GlfwErrorCode GLFW::GetLastError() {
        return err;
    }

} // namespace Window