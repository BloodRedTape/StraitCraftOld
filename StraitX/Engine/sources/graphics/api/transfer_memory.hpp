#ifndef STRAITX_TRANSFER_MEMORY_HPP
#define STRAITX_TRANSFER_MEMORY_HPP

#include "core/array_ptr.hpp"
#include "core/math/vector2.hpp"
#include "graphics/api/gpu_texture_view.hpp"

namespace StraitX{

struct TransferMemory{
    union {
        void *Pointer;
        struct {
            u64 MemHandle;
            u64 BufHandle;
        };
    }Handle;

};

}//namesapce StraitX::

#endif //STRAITX_TRANSFER_MEMORY_HPP