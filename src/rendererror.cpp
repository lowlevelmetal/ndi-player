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
        }

        return std::string("Invalid render error code");
    }

} // namespace Render