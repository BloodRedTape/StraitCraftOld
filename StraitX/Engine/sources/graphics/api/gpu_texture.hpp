#ifndef STRAITX_GPU_TEXTURE_HPP
#define STRAITX_GPU_TEXTURE_HPP

#include "graphics/api/gpu_configuration.hpp"

namespace StraitX{

namespace GL{
class GPUTextureImpl;
}//namesapce GL::

namespace Vk{
class GPUTextureImpl;
}//namespace Vk::

enum class TextureLayout{
    Undefined = 0,
    General,
    ColorAttachmentOptimal,
    DepthStencilAttachmentOptimal,
    TransferSrcOptimal,
    TransferDstOptimal,
    PresentSrcOptimal
};

class GPUTexture{
private:
    GPUResourceHandle m_Handle = {};
    TextureLayout m_Layout;
    Format m_TextureFromat;
public:


};

}//namesapce StraitX::

#endif //STRAITX_GPU_TEXTURE_HPP 