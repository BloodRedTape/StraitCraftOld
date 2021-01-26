#ifndef MESH_HPP
#define MESH_HPP

#include "core/array_ptr.hpp"
#include "buffer.hpp"

using namespace StraitX;

struct Mesh{
    Buffer VertexBuffer;
    Buffer IndexBuffer;
    u32 ElementsCount = 0;

    void Create(void *vertex_data, size_t vsize, u32 *index_data, size_t isize);

    void Destroy();
};

#endif // MESH_HPP