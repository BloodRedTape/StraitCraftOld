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

Vertex Vertices[]={
    {{ 50,  0, 0.0},{1,0,0}},
    {{-50,  0, 0.0},{0,1,0}},
    {{  0, 50, 0.0},{0,0,1}}
};

Vertex Cube[]={
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},

    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},

    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},

    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}},
    {{ 0.5,  0.5, 0.5},{1,0,0}}
};

u32 Indices[] = {
    2, 1, 0
};

FPSCamera PlayerCamera = Camera::Orthographic(WindowSize.x, WindowSize.y, 0, 50000);

Result StraitCraft::OnInitialize(){
    Mouse::SetVisible(false, DisplayServer::Instance().GetWindow());

    m_Renderer.Initialize();

    //m_Chunk->Data[12][12][255] = Block::Air;
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
        /*
        for(int i = 0; i < 20; i++){
            for(int j = 0; j<20; j++)
                Block(i,0,j,Block::Grass);
        }
        for(int i = 0; i < (int)Block::BlocksCount; i++)
            Block(i,1,9,(Block)i);
        
        Block(3,1,3,Block::Emerald);
        Block(3,1,4,Block::Iron);
        Block(3,2,4,Block::Iron);
        Block(3,3,4,Block::Iron);
        Block(3,4,4,Block::Gold);
        Block(3,1,5,Block::Emerald);
        

        Tree(6,1,6);

        Tree(16,1,12);

        Tree(1,1,18);
        */

        m_World.Draw(m_Renderer.m_ChunkRenderer);
    }
    m_Renderer.EndFrame();


}
    
Result StraitCraft::OnFinalize(){

    m_Renderer.Finalize();

    return Result::Success;
}