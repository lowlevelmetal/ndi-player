/*
 * ndi-player
 * framebuffer.cpp
 *
 * 02-26-2023
 * Matthew Todd Geiger
 */

// Standard includes
#include <cstring>

// Local includes
#include "framebuffer.hpp"

namespace Render {
    // Operator overloads
    YUV422FrameBuffer::operator uint8_t*() const {
        return m_framebuffer;
    }

    YUV422FrameBuffer::operator uint8_t*const*() const {
        return &m_framebuffer;
    }

    uint8_t& YUV422FrameBuffer::operator[](int index) const {
        if(m_framebuffer == nullptr)
            throw RenderErrorCode::UninitializedFramebuffer;
        
        if(index >= m_size)
            throw RenderErrorCode::OutOfBounds;

        return m_framebuffer[index];
    }

    // Constructors
    YUV422FrameBuffer::YUV422FrameBuffer() {}

    YUV422FrameBuffer::YUV422FrameBuffer(size_t width, size_t height) {
        Alloc(width, height);
    }

    YUV422FrameBuffer::YUV422FrameBuffer(size_t size) {
        Alloc(m_size);
    }

    YUV422FrameBuffer::~YUV422FrameBuffer() {
        Dealloc();
    }

    // Member functions
    void YUV422FrameBuffer::Dealloc() {
        if(m_framebuffer && !m_inherited)
            delete[] m_framebuffer;

        m_framebuffer = nullptr;
    }

    // This will almost always be the fastest
    void YUV422FrameBuffer::Alloc(size_t width, size_t height) {
        if(m_framebuffer)
            throw RenderErrorCode::InitializedFramebuffer;

        // Calculate the size of memory needed for Y, U, and V planes
        size_t size = (width * 2) * height;

        // Allocate memory
        m_framebuffer = new uint8_t[size];

        // Set width and height
        resx = width;
        resy = height;
        m_size = size;
    }

    void YUV422FrameBuffer::Alloc(size_t size) {
        if(m_framebuffer)
            throw RenderErrorCode::InitializedFramebuffer;

        m_framebuffer = new uint8_t[size];

        // Size of one pixel in bytes (Y + U/V)
        const size_t pixel_size = 2;
        size_t num_pixels = size / pixel_size;
        for (int w = 1; w <= num_pixels; ++w) {
            if (num_pixels % w == 0) {
                resx = w;
                resy = num_pixels / resx;
                break;
            }
        }

        m_size = size;
    }

    void YUV422FrameBuffer::Lock() {
        m_framebufferlock.lock();
    }

    void YUV422FrameBuffer::Unlock() {
        m_framebufferlock.unlock();
    }

    bool YUV422FrameBuffer::IsInitialized() {
        return m_framebuffer == nullptr ? true : false;
    }

    void YUV422FrameBuffer::Inherit(size_t width, size_t height, uint8_t *framebuffer) {
        if(!framebuffer)
            throw RenderErrorCode::UninitializedFramebuffer;
        
        m_inherited = true;

        resx = width;
        resy = height;
        m_framebuffer = framebuffer;
        m_size = (width * 2) * height;
    }

    void YUV422FrameBuffer::Uninherit() {
        if(!m_inherited)
            return;
        
        m_inherited = false;
        m_framebuffer = nullptr;
    }

    void YUV422FrameBuffer::Copy(size_t width, size_t height, uint8_t *framebuffer) {
        size_t size = (width * 2) * height;
        if(size > m_size)
            throw RenderErrorCode::OutOfBounds;

        memcpy(m_framebuffer, framebuffer, size);
    }

} // namespace Render