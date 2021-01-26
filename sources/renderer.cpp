#include "renderer.hpp"

#define AssertRes(x) Assert(x == Result::Success)


void Renderer::Initialize(){
    AssertRes(m_Context.Create(m_Window, {4, 6, 0}));
    AssertRes(m_Context.MakeCurrent());
    
    glEnable(GL_DEPTH);
    glEnable(GL_DEPTH_TEST);

    glClearColor(m_SkyColor.x, m_SkyColor.y, m_SkyColor.z, 1.0);

    m_ChunkRenderer.Initialize();
}

void Renderer::BeginFrame(const FPSCamera &camera){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_ChunkRenderer.BeginFrame(camera);
}


void Renderer::EndFrame(){
    m_ChunkRenderer.EndFrame();

    m_Context.SwapBuffers();
}

void Renderer::Finalize(){
    m_ChunkRenderer.Finalize();

    m_Context.Destroy();
}