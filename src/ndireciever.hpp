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
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>

// local includes
#include "ndi.hpp"
#include "framebuffer.hpp"

namespace AV {

    class NDIReciever : public NDI {
        public:
            NDIReciever();
            NDIReciever(std::string mdns, std::string sender_id);

            ~NDIReciever();

        private:
            std::mutex m_framebuffer_lock;
            std::atomic<bool> m_shutdown;
            NDIlib_recv_instance_t m_pNDI_recv = nullptr;
            std::shared_ptr<std::thread> m_video_thread;

            AvErrorCode m_FindInstanceAndCreate(const char *const mdns = nullptr, const char *const sender_id = nullptr);
            static void m_VideoThread(NDIlib_recv_instance_t pNDI_recv, std::atomic<bool> &shutdown, Render::YUV422FrameBuffer &framebuffer);

        protected:
            Render::YUV422FrameBuffer m_frame_buffer;
    };

}

