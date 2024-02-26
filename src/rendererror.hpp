/*
 * ndi-player
 * rendererror.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <string>

namespace Render {

    enum class RenderErrorCode {
        NoError,
        GlewInit
    };

    std::string RenderErrorStr(RenderErrorCode &err);

} // namespace Render
