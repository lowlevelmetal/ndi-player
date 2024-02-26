/*
 * ndi-player
 * glew.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// local includes
#include "rendererror.hpp"

// GLEW includes
#include <GL/glew.h>

namespace Render {
    class GLEW {
        public:
            GLEW();

            RenderErrorCode GetLastError();

        private:
            static bool initialized;

        protected:
            RenderErrorCode last_error;

    };
}