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

constexpr size_t MaxFacesCount = 200000;
constexpr u32 MaxTexturesCount = 16;
struct FaceVertexData{
    Vertex Vertices[4];

    static FaceVertexData Move(const FaceVertexData &face, const Vector3i &position, const Pair<Vector2f,Vector2f> &tex_coords);
};
struct FaceIndexData{
    u32 Indices[6];

    static FaceIndexData Bias(const FaceIndexData &indices, u32 face_number);
};

class BlockRenderer{
private:
    TextureAtlas Atlas;

    Shader Shaders[2];
    GraphicsPipeline Pipeline;

    Buffer   VertexBuffer;
    Buffer   IndexBuffer;
    Buffer   UniformBuffer;

    u32 PendingFacesCount = 0;

    FaceVertexData StagingVertexBuffer[MaxFacesCount];

    FaceIndexData StagingIndexBuffer[MaxFacesCount];

    struct {
        Matrix4f Projection;
        Matrix4f View;
        float FOV;
    }StagingUnifromBuffer;

public:
    enum class Face{
        Top = 0,
        Bottom,
        Left,
        Right,
        Front,
        Back,

        ElementsCount
    };
    void Initialize();

    void BeginFrame(const FPSCamera &camera);

    void BeginBatch();

    void Draw(const Vector3i &position, Face face, Block block);

    void EndBatch();

    void EndFrame();

    void Finalize();
};

#endif //CUBE_RENDERER_HPP 