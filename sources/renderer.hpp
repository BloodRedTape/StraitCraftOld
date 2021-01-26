#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "platform/glcontext.hpp"
#include "platform/opengl.hpp"
#include "servers/display_server.hpp"
#include "chunk_renderer.hpp"

using namespace StraitX;

class Renderer{
private:
    GLContext m_Context;
    Window &m_Window = DisplayServer::Instance().GetWindow();
    const Vector3f m_SkyColor = {0.2, 0.8, 1.0};
public:
    ChunkRenderer m_ChunkRenderer;

    void Initialize();

    void BeginFrame(const FPSCamera &camera);


    void EndFrame();

    void Finalize();
};

#endif // RENDERER_HPP