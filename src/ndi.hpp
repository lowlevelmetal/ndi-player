/*
 * ndi-player
 * ndi.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <cstdlib>

// Local includes
#include "averror.hpp"

// NDI Includes
#include <Processing.NDI.Lib.h>

namespace AV {

    class NDI {
        public:
            NDI();
            ~NDI();

            AvErrorCode GetLastError();

        private:
            static int m_open_instances;

        protected:
            AvErrorCode last_error = AvErrorCode::NoError;
    };

} // namespace AV

