#include "mesh_renderer.hpp"


void MeshRenderer::Initialize(){
    Shaders[0].Create("shaders/mesh.frag.glsl", GL_FRAGMENT_SHADER);
    Shaders[1].Create("shaders/mesh.vert.glsl", GL_VERTEX_SHADER);

    VertexAttribute attrs[] = {
        VertexAttribute::Float3,
        VertexAttribute::Float2
    };

    Pipeline.Create({Shaders, sizeof(Shaders)/sizeof(Shader)}, {attrs, sizeof(attrs)/sizeof(VertexAttribute)});
    Pipeline.Bind();
    glUniform1i(Pipeline.UniformLocation("u_Texture"),0);

    UniformBuffer.Create(sizeof(StagingUniform), GPUMemoryTypes::DynamicVRAM);
    Pipeline.BindUniformBuffer(UniformBuffer, 0);
}

void MeshRenderer::BeginFrame(const FPSCamera &camera){
    Pipeline.Bind();

    StagingUniform.Projection = Transpose(camera.Projection);
    StagingUniform.View = Transpose(camera.GetView());
    StagingUniform.FOV = camera.FOV;

    UniformBuffer.UploadData(sizeof(StagingUniform), 0, &StagingUniform); 
}

void MeshRenderer::Draw(const Mesh &mesh){
    Pipeline.DrawElements(RasterizationMode::TrianglesList, mesh.VertexBuffer, mesh.IndexBuffer, mesh.ElementsCount); 
}

void MeshRenderer::EndFrame(){
    
}

void MeshRenderer::Finalize(){
    UniformBuffer.Destroy();

    Shaders[0].Destroy();
    Shaders[1].Destroy();

    // TODO Pipeline.Destroy();
}