/*
 * ndi-player
 * framebuffer.hpp
 *
 * 02-26-2023
 * Matthew Todd Geiger
 */

#pragma once

// Standard includes
#include <cstdint>
#include <mutex>

// Local includes
#include "rendererror.hpp"

namespace Render {

    // Partially atomic framebuffer type
    class YUV422FrameBuffer {
        public:
            YUV422FrameBuffer();
            YUV422FrameBuffer(size_t width, size_t height);
            YUV422FrameBuffer(size_t size);
            ~YUV422FrameBuffer();

            void Lock();
            void Unlock();
            void Alloc(size_t width, size_t height);
            void Alloc(size_t size);
            void Dealloc();
            void Inherit(size_t width, size_t height, uint8_t *framebuffer);
            void Uninherit();
            bool IsInitialized();
            
            // I want to be able to access framebuffer data like a generic pointer
            operator uint8_t*() const;
            operator uint8_t*const*() const;
            uint8_t& operator[](int index) const;

            int resx = 0;
            int resy = 0;

        private:
            std::mutex m_framebufferlock;
            uint8_t *m_framebuffer = nullptr;
            size_t m_size = 0;
            bool m_inherited = false;

    };

} // namespace Render