#ifndef GRAPHICS_PIPELINE_HPP
#define GRAPHICS_PIPELINE_HPP

#include <vector>
#include "platform/opengl.hpp"
#include "platform/types.hpp"
#include "platform/file.hpp"
#include "platform/io.hpp"
#include "core/array_ptr.hpp"
#include "shader.hpp"
#include "buffer.hpp"
#include "attributes.hpp"

using namespace StraitX;


enum RasterizationMode{
    TrianglesList,
    PointsLits,
    LinesList,
    LinesStrip
};

class GraphicsPipeline{
private:
    u32 VertexArray = 0;
    u32 Program = 0;
    std::vector<VertexAttribute> Attributes;
    u32 AttributesStride = 0;
public:
    void Create(const ArrayPtr<Shader> &shaders, const ArrayPtr<VertexAttribute> &vertex_attributes);

    void Bind();

    void BindUniformBuffer(const Buffer &buffer, u32 index);

    void DrawElements(RasterizationMode mode, const Buffer &vertex_buffer, const Buffer &index_buffer, u32 count);

    void Draw(RasterizationMode mode, const Buffer &vertex_buffer, u32 count);

    int UniformLocation(const char *name);

private:
    static GLenum ToGlDrawMode(RasterizationMode mode);

    static u32 CreateProgram(const ArrayPtr<Shader> &shaders);

    void BindVertexBuffer(const Buffer &buffer);

    void BindIndexBuffer(const Buffer &buffer);
};

#endif ///GRAPHICS_HPP