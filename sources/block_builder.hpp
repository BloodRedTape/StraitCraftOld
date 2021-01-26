#ifndef CUBE_RENDERER_HPP
#define CUBE_RENDERER_HPP

#include "platform/opengl.hpp"
#include "platform/glcontext.hpp"
#include "core/math/vector3.hpp"
#include "blocks.hpp"
#include "graphics_pipeline.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "camera.hpp"
#include "types.hpp"

using namespace StraitX;


struct FaceVertexData{
    Vertex Vertices[4];

    static FaceVertexData Move(const FaceVertexData &face, const Vector3i &position, const Pair<Vector2f,Vector2f> &tex_coords);
};

struct FaceIndexData{
    u32 Indices[6];

    FaceIndexData &Bias(u32 face_number);
};

enum class BlockFace{
    Top = 0,
    Bottom,
    Left,
    Right,
    Front,
    Back,

    ElementsCount
};

constexpr float BlockSize = 50;

void BuildBlock(const Vector3i &position, BlockFace face, Block block, FaceVertexData &vertex_data, FaceIndexData &index_data);

#endif //CUBE_RENDERER_HPP 