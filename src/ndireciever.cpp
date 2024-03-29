/*
 * ndi-player
 * ndireciever.cpp
 *
 * 02-25-2023
 * Matthew Todd Geiger
 */

// Standard includes
#include <cstring>

// local includes
#include "ndireciever.hpp"
#include "macro.hpp"

namespace AV {

    // Thread functions
    void NDIReciever::m_VideoThread(NDIlib_recv_instance_t pNDI_recv,  std::atomic<bool> &shutdown, Render::YUV422FrameBuffer &m_frame_buffer) {
        DEBUG("Video thread launched");

        uint frame_count = 0;
        while(!shutdown) {
            NDIlib_video_frame_v2_t video_frame;

            if(NDIlib_recv_capture_v2(pNDI_recv, &video_frame, nullptr, nullptr, 5000) != NDIlib_frame_type_video) {
                ERROR("Failed to capture video frame");
                continue;
            }

            if(video_frame.FourCC != NDIlib_FourCC_video_type_UYVY) {
                ERROR("Unsupported pixel format");
                goto END;
            }

            DEBUG("Captured Video Frame\n"
                    "\tFrame: %d\n"
                    "\tWidth: %d\n"
                    "\tHeight: %d\n\n", frame_count, video_frame.xres, video_frame.yres);

            frame_count++;

            m_frame_buffer.Lock();
            if(m_frame_buffer.resx != video_frame.yres || m_frame_buffer.resy != video_frame.yres) {
                m_frame_buffer.Dealloc();
                m_frame_buffer.Alloc(video_frame.xres, video_frame.yres);
            }

            m_frame_buffer.Copy(video_frame.xres, video_frame.yres, video_frame.p_data);
            m_frame_buffer.Unlock();

END:
            NDIlib_recv_free_video_v2(pNDI_recv, &video_frame);
        }

    }

    NDIReciever::NDIReciever() : NDI(), m_shutdown(false) {
        if(last_error != AvErrorCode::NoError) {
            DEBUG("Error detected in NDI init");
            return;
        }

        if((last_error = m_FindInstanceAndCreate()) != AvErrorCode::NoError) {
            DEBUG("Error detected in FindInstanceAndCreate");
            return;
        }

        m_video_thread = std::make_shared<std::thread>(m_VideoThread, m_pNDI_recv, std::ref(m_shutdown), std::ref(m_frame_buffer));
    }

    NDIReciever::NDIReciever(std::string mdns, std::string sender_id) : NDI(), m_shutdown(false) {
        if(last_error != AvErrorCode::NoError) {
            DEBUG("Error detected in NDI init");
            return;
        }

        if((last_error = m_FindInstanceAndCreate(mdns.c_str(), sender_id.c_str())) != AvErrorCode::NoError) {
            DEBUG("Error detected in FindInstanceAndCreate");
            return;
        }

        m_video_thread = std::make_shared<std::thread>(m_VideoThread, m_pNDI_recv, std::ref(m_shutdown), std::ref(m_frame_buffer));
    }

    NDIReciever::~NDIReciever() {
        m_shutdown = true;

        if(m_video_thread)
            m_video_thread->join();

        if(m_pNDI_recv)
            NDIlib_recv_destroy(m_pNDI_recv);
    }

    AvErrorCode NDIReciever::m_FindInstanceAndCreate(const char *const mdns, const char *const sender_id) {
        bool auto_select = false;

        if(!mdns && !sender_id)
            auto_select = true;
        else if(mdns && !sender_id)
            return (last_error = AvErrorCode::InvalidConfiguration);
        else if(sender_id && !mdns)
            return (last_error = AvErrorCode::InvalidConfiguration);

        NDIlib_find_instance_t pNDI_find = NDIlib_find_create_v2();
        if(!pNDI_find)
            return (last_error = AvErrorCode::CreateFindInstance);

        // Look for a server to connect to
        AvErrorCode ret = AvErrorCode::NoError;
        uint32_t num_sources = 0;
        const NDIlib_source_t *p_sources = nullptr;
        while(!num_sources) {
            DEBUG("Looking for NDI sources");
            NDIlib_find_wait_for_sources(pNDI_find, 1000);
            p_sources = NDIlib_find_get_current_sources(pNDI_find, &num_sources);
        } 

        m_pNDI_recv = NDIlib_recv_create_v3();
        if(!m_pNDI_recv) {
            ret = AvErrorCode::CreateRecvInstance;
            goto END;
        }

        // Connect to source
        if(auto_select) {
            NDIlib_recv_connect(m_pNDI_recv, p_sources + 0);
        } else {
            char ndi_name[1024];
            std::snprintf(ndi_name, 1023, "%s (%s)", mdns, sender_id);

            for(int i = 0; i < num_sources; i++) {
                DEBUG("%s", p_sources[i].p_ndi_name);
                if(!std::strncmp(ndi_name, p_sources[i].p_ndi_name, 1023)) {
                    NDIlib_recv_connect(m_pNDI_recv, p_sources + i);
                    goto END;
                }
            }

            ret = AvErrorCode::NoSources;
        }

END:
        if(pNDI_find)
            NDIlib_find_destroy(pNDI_find);

        return (last_error = ret);
    }

} // namespace AV