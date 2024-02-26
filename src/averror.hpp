/*
 * ndi-player
 * averror.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Standard includes
#include <string>

namespace AV {

    enum class AvErrorCode {
        NoError,
        NdiInit,
        CreateFindInstance,
        InvalidConfiguration,
        CreateRecvInstance,
        NoSources
    };

    std::string AvErrorStr(AvErrorCode &err);

} // namespace AV