#include "graphics_pipeline.hpp"
#include "debug.hpp"

void GraphicsPipeline::Create(const ArrayPtr<Shader> &shaders, const ArrayPtr<VertexAttribute> &vertex_attributes){
    glGenVertexArrays(1, &VertexArray); 

    glBindVertexArray(VertexArray);

    AttributesStride = CalcStride(vertex_attributes);

    for(int i = 0; i<vertex_attributes.Size; i++){
        glEnableVertexAttribArray(i);
        glVertexAttribFormat(i, ElementsCount(vertex_attributes[i]), ElementType(vertex_attributes[i]), false, 0/*vertex buffer offset*/);
        glVertexAttribBinding(i, i);
    }
    
    Attributes.reserve(vertex_attributes.Size);
    for(auto &attr: vertex_attributes)
        Attributes.push_back(attr);

    Program = CreateProgram(shaders);
}

void GraphicsPipeline::Bind(){
    glBindVertexArray(VertexArray);

    glUseProgram(Program);
}

void GraphicsPipeline::BindUniformBuffer(const Buffer &buffer, u32 index){
    glBindBufferBase(GL_UNIFORM_BUFFER, index, buffer.Id);
}

void GraphicsPipeline::DrawElements(RasterizationMode mode, const Buffer &vertex_buffer, const Buffer &index_buffer, u32 count){
    BindVertexBuffer(vertex_buffer);
    BindIndexBuffer(index_buffer);
    GL(glDrawElements(ToGlDrawMode(mode), count, GL_UNSIGNED_INT, nullptr));
}

void GraphicsPipeline::Draw(RasterizationMode mode, const Buffer &vertex_buffer, u32 count){
    BindVertexBuffer(vertex_buffer);
    GL(glDrawArrays(ToGlDrawMode(mode), 0, count));
}

int GraphicsPipeline::UniformLocation(const char *name){
    auto res = glGetUniformLocation(Program, name);
    Assert(res != -1);
    return res;
}

GLenum GraphicsPipeline::ToGlDrawMode(RasterizationMode mode){
    switch (mode)
    {
    case TrianglesList:
        return GL_TRIANGLES;
    case LinesList:
        return GL_LINES;
    case PointsLits:
        return GL_POINTS;
    case LinesStrip:
        return GL_LINE_STRIP;
    }
    return GL_FALSE;
}

u32 GraphicsPipeline::CreateProgram(const ArrayPtr<Shader> &shaders){
    u32 program = glCreateProgram();
    for(auto &shader: shaders)
        glAttachShader(program, shader.Id);

    glLinkProgram(program);

    int status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if(status != GL_TRUE)
        LogError("OpenGL: Program: Linkage Failed");
    return program;
}

void GraphicsPipeline::BindVertexBuffer(const Buffer &buffer){
    u32 offset = 0;
    for(size_t i = 0; i < Attributes.size(); i++){
        glBindVertexBuffer(i, buffer.Id, offset, AttributesStride);
        offset += ElementsCount(Attributes[i])*4;
    }
}

void GraphicsPipeline::BindIndexBuffer(const Buffer &buffer){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.Id);
}