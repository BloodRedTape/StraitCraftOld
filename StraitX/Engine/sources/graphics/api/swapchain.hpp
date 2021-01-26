#ifndef STRAITX_SWAPCHAIN_HPP
#define STRAITX_SWAPCHAIN_HPP

#include "graphics/api/framebuffer.hpp"

namespace StraitX{

class Swapchain{
private:

public:

    const Framebuffer &CurrentFramebuffer();

    void SwapBuffers();
};

}//namesapce StraitX::

#endif //STRAITX_SWAPCHAIN_HPP