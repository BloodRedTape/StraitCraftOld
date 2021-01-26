#include "straitcraft.hpp"
#include "platform/io.hpp"
#include "platform/opengl.hpp"
#include "core/math/matrix4.hpp"
#include "core/assert.hpp"
#include "types.hpp"
#include "camera.hpp"
#include "math.hpp"

#define Block(x,y,z, block)do{\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Top,     block);\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Bottom,  block);\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Left,    block);\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Right,   block);\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Front,   block);\
    m_Renderer.m_BlockRenderer.Draw({x,y,z}, BlockRenderer::Face::Back,    block);}while(0)


#define Tree(x,y,z)do{\
    Block(x,y+0,z, Block::OakLog);\
    Block(x,y+1,z, Block::OakLog);\
    Block(x,y+2,z+1, Block::OakLeaves);\
    Block(x+1,y+2,z, Block::OakLeaves);\
    Block(x,y+2,z-1, Block::OakLeaves);\
    Block(x-1,y+2,z, Block::OakLeaves);\
    Block(x-1,y+2,z+1, Block::OakLeaves);\
    Block(x+1,y+2,z+1, Block::OakLeaves);\
    Block(x+1,y+2,z-1, Block::OakLeaves);\
    Block(x-1,y+2,z-1, Block::OakLeaves);\
    Block(x,y+3,z+1, Block::OakLeaves);\
    Block(x+1,y+3,z, Block::OakLeaves);\
    Block(x,y+3,z-1, Block::OakLeaves);\
    Block(x-1,y+3,z, Block::OakLeaves);\
    Block(x,y+3,z, Block::OakLeaves);\
}while(0)

sx_inline Vector2f ToVec(Point point){
    return Vector2f(point.x, point.y);
}

StraitCraft::StraitCraft():
    Application("StraitCraft")
{

}

StraitCraft::~StraitCraft(){

}

Vector2i WindowSize(GameConfig.WindowSize);
Vector2i ScreenSize(1920, 1080);

FPSCamera PlayerCamera = Camera::Orthographic(WindowSize.x, WindowSize.y, 0, 50000);

Result StraitCraft::OnInitialize(){
    Mouse::SetVisible(false, DisplayServer::Instance().GetWindow());

    m_Renderer.Initialize();

    Atlas.Initialize();
    Atlas.MainTexture.Bind(0);

    m_World = new World{Vector2u(32, 32), 234234234};

    PlayerCamera.MoveY(50 * 30);

    return Result::Success;
}

bool StraitCraft::OnEvent(const Event &e){
    return false;
}

void StraitCraft::OnUpdate(float dt){
    LogInfo("FPS: %", 1/dt);

    if(Keyboard::IsKeyPressed(Keyboard::Q))
        Stop();


    auto cur_pos = Mouse::GlobalPosition();
    Mouse::SetGlobalPosition({ScreenSize.x/2,ScreenSize.y/2});

    constexpr float sensitivity = 22;
    PlayerCamera.Rotate((ScreenSize.y - cur_pos.y - ScreenSize.y/2)/sensitivity, (cur_pos.x - ScreenSize.x/2)/sensitivity);

    float speed = 400 * dt; 
    

    if(Keyboard::IsKeyPressed(Keyboard::W))
        PlayerCamera.MoveXZ({0,  speed});
    if(Keyboard::IsKeyPressed(Keyboard::S))
        PlayerCamera.MoveXZ({0, -speed});

    if(Keyboard::IsKeyPressed(Keyboard::A))
        PlayerCamera.MoveXZ({-speed,0});
    if(Keyboard::IsKeyPressed(Keyboard::D))
        PlayerCamera.MoveXZ({ speed,0});
    if(Keyboard::IsKeyPressed(Keyboard::LeftShift))
        PlayerCamera.MoveY(-speed);
    if(Keyboard::IsKeyPressed(Keyboard::Space))
        PlayerCamera.MoveY( speed);
    

    m_Renderer.BeginFrame(PlayerCamera);
    {
        m_World->Render(m_Renderer.m_MeshRenderer);
    }
    m_Renderer.EndFrame();


}
    
Result StraitCraft::OnFinalize(){

    delete m_World;

    Atlas.Finalize();

    m_Renderer.Finalize();

    return Result::Success;
}