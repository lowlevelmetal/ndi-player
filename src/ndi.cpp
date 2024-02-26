/*
 * ndi-player
 * ndi.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// local includes
#include "ndi.hpp"

// local includes
#include "ndi.hpp"

namespace AV {
    int NDI::m_open_instances = 0;

    NDI::NDI() {
        if(!m_open_instances) {
            if(!NDIlib_initialize()) {
                last_error = AvErrorCode::NdiInit;
                return;
            }
        }

        m_open_instances++;
    }

    NDI::~NDI() {
        m_open_instances--;

        if(!m_open_instances) {
            NDIlib_destroy();
        }
    }

    AvErrorCode NDI::GetLastError() {
        return last_error;
    }

} // namespace AV