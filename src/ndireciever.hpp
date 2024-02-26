/*
 * ndi-player
 * ndireciever.hpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <string>

// local includes
#include "ndi.hpp"

namespace AV {

    class NDIReciever : public NDI {
        public:
            NDIReciever();
            NDIReciever(std::string mdns, std::string sender_id);

            ~NDIReciever();

        private:
            NDIlib_recv_instance_t m_pNDI_recv = nullptr;

            AvErrorCode m_FindInstanceAndCreate(const char *const mdns = nullptr, const char *const sender_id = nullptr);
    };

}

