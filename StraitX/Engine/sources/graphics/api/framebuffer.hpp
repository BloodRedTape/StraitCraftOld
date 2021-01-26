#ifndef STRAITX_FRAMEBUFFER_HPP
#define STRAITX_FRAMEBUFFER_HPP

#include "core/array_ptr.hpp"
#include "core/math/vector2.hpp"
#include "graphics/api/gpu_texture_view.hpp"

namespace StraitX{

class Framebuffer{
private:
    ArrayPtr<GPUTextureView*, u32> m_ColorAttachments = {};
    GPUTextureView *m_DepthStencil = nullptr;
    Vector2u m_Size = {};
public:

};

}//namesapce StraitX::

#endif //STRAITX_FRAMEBUFFER_HPP 