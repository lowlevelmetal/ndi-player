/*
 * ndi-player
 * averror.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Local includes
#include "averror.hpp"

namespace AV {
    std::string AvErrorStr(AvErrorCode &err) {
        switch(err) {
            case AvErrorCode::NoError:
                return std::string("No AV error code detected");
            case AvErrorCode::NdiInit:
                return std::string("Failed to initialize NDI SDK");
            case AvErrorCode::CreateFindInstance:
                return std::string("Failed to create NDI find instance");
            case AvErrorCode::InvalidConfiguration:
                return std::string("Invalid configuration");
            case AvErrorCode::CreateRecvInstance:
                return std::string("Failed to create NDI recv instance");
            case AvErrorCode::NoSources:
                return std::string("Failed to find NDI source");
        }

        return std::string("Invalid AV error code");
    }

}