/*
 * ndi-player
 * glew.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// local includes
#include "glew.hpp"
#include "macro.hpp"

namespace Render {

    bool GLEW::initialized = false;

    GLEW::GLEW() {
        if(!initialized) {
            if(!glewInit()) {
                last_error = RenderErrorCode::GlewInit;
                DEBUG("GLEW init error detected");
                return;
            }

            initialized = true;
        }
    }

    RenderErrorCode GLEW::GetLastError() {
        return last_error;
    }

} // namespace Render