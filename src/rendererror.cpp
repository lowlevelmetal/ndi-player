/*
 * ndi-player
 * rendererror.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// local includes
#include "rendererror.hpp"

namespace Render {

    std::string RenderErrorStr(RenderErrorCode &err) {
        switch(err) {
            case RenderErrorCode::NoError:
                return std::string("No render error");
            case RenderErrorCode::GlewInit:
                return std::string("Failed to initialize GLEW");
            case RenderErrorCode::OutOfBounds:
                return std::string("Attempted to access out of bounds memory");
            case RenderErrorCode::UninitializedFramebuffer:
                return std::string("Attempted to use initialized framebuffer");
            case RenderErrorCode::InitializedFramebuffer:
                return std::string("Framebuffer is already initialized");
        }

        return std::string("Invalid render error code");
    }

} // namespace Render