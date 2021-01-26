#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include "mesh.hpp"
#include "graphics_pipeline.hpp"
#include "camera.hpp"




struct MeshRenderer{
    GraphicsPipeline Pipeline;

    struct{
        Matrix4f Projection;
        Matrix4f View;
        float FOV;
    }StagingUniform;
    Buffer UniformBuffer;

    Shader Shaders[2];

    void Initialize();

    void BeginFrame(const FPSCamera &camera);

    void Draw(const Mesh &mesh);

    void EndFrame();

    void Finalize();
};

#endif//MESH_RENDERER_HPP