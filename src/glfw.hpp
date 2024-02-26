/*
 * ndi-player
 * glfw.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// local includes
#include "glfwerror.hpp"

// GLFW3 includes
#include <GLFW/glfw3.h>


namespace Window {

    class GLFW {
        public:
            GLFW();
            ~GLFW();

            GlfwErrorCode GetLastError();

        private:
            static int m_open_instances;

        protected:
            GlfwErrorCode err = GlfwErrorCode::NoError;
    };

} // namespace Window