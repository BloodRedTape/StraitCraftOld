#ifndef ATTRS_HPP
#define ATTRS_HPP

#include "platform/types.hpp"
#include "platform/opengl.hpp"
#include "platform/io.hpp"
#include "core/array_ptr.hpp"

using namespace StraitX;

enum class VertexAttribute: u8{
    Float,
    Float2,
    Float3,
    Float4,
    Int,
    Int2,
    Int3,
    Int4,
    Uint,
    Uint2,
    Uint3,
    Uint4
};

inline u32 ElementsCount(VertexAttribute attrib){
    switch (attrib) {
    case VertexAttribute::Float:
    case VertexAttribute::Int:
    case VertexAttribute::Uint:
        return 1;
    case VertexAttribute::Float2:
    case VertexAttribute::Int2:
    case VertexAttribute::Uint2:
        return 2;
    case VertexAttribute::Float3:
    case VertexAttribute::Int3:
    case VertexAttribute::Uint3:
        return 3;
    case VertexAttribute::Float4:
    case VertexAttribute::Int4:
    case VertexAttribute::Uint4:
        return 4;
    }
    return 0;
}

inline GLenum ElementType(VertexAttribute attrib){
    switch (attrib) {
    case VertexAttribute::Float:
    case VertexAttribute::Float2:
    case VertexAttribute::Float3:
    case VertexAttribute::Float4:
        return GL_FLOAT;
    case VertexAttribute::Int:
    case VertexAttribute::Int2:
    case VertexAttribute::Int3:
    case VertexAttribute::Int4:
        return GL_INT;
    case VertexAttribute::Uint:
    case VertexAttribute::Uint2:
    case VertexAttribute::Uint3:
    case VertexAttribute::Uint4:
        return GL_UNSIGNED_INT;
    }
    Output::Print("================Shit=============");
    return GL_FALSE;
}

inline u32 CalcStride(const ArrayPtr<VertexAttribute> &vertex_attributes){
    u32 stride = 0;
    for(auto &attr: vertex_attributes)
        stride += ElementsCount(attr)*4;
    return stride;
}


#endif //ATTRS_HPP