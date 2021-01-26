#include "servers/display_server.hpp"
#include "block_renderer.hpp"
#include "types.hpp"

constexpr float side = 50;




FaceVertexData FaceVertexData::Move(const FaceVertexData &face, const Vector3i &position, const Pair<Vector2f,Vector2f> &tex_coords){
    FaceVertexData data = face;
    for(int i = 0; i<4; i++){
        data.Vertices[i].Position += Vector3f(position)*side;
    }
    data.Vertices[0].TexCoords = {tex_coords.First.x, tex_coords.First.y + tex_coords.Second.y};
    data.Vertices[1].TexCoords = {tex_coords.First.x + tex_coords.Second.x, tex_coords.First.y + tex_coords.Second.y};
    data.Vertices[2].TexCoords = {tex_coords.First.x, tex_coords.First.y};
    data.Vertices[3].TexCoords = {tex_coords.First.x + tex_coords.Second.x, tex_coords.First.y};
    return data;
}

FaceIndexData FaceIndexData::Bias(const FaceIndexData &indices, u32 face_number){
    FaceIndexData data = indices;

    for(int i = 0; i<6; i++)
        data.Indices[i] += 4 * face_number;

    return data;
}

FaceVertexData FaceVertices[(int)BlockRenderer::Face::ElementsCount]{
    { // Face::Top
        Vertex{{ -side/2,   side/2,  side/2},{0,0,0}, {0,1}},
        Vertex{{  side/2,   side/2,  side/2},{1,0,0}, {1,1}},
        Vertex{{ -side/2,   side/2, -side/2},{0,1,0}, {0,0}},
        Vertex{{  side/2,   side/2, -side/2},{1,1,0}, {1,0}}
    },
    { // Face::Bottom
        Vertex{{  side/2,  -side/2,  side/2},{0,0,0}, {0,1}},
        Vertex{{ -side/2,  -side/2,  side/2},{1,0,0}, {1,1}},
        Vertex{{  side/2,  -side/2, -side/2},{0,1,0}, {0,0}},
        Vertex{{ -side/2,  -side/2, -side/2},{1,1,0}, {1,0}}
    },
    { // Face::Left
        Vertex{{ -side/2,   side/2,  side/2},{0,0,0}, {0,1}},
        Vertex{{ -side/2,   side/2, -side/2},{1,0,0}, {1,1}},
        Vertex{{ -side/2,  -side/2,  side/2},{0,1,0}, {0,0}},
        Vertex{{ -side/2,  -side/2, -side/2},{1,1,0}, {1,0}}
    },
    { // Face::Right
        Vertex{{  side/2,   side/2, -side/2},{0,0,0}, {0,1}},
        Vertex{{  side/2,   side/2,  side/2},{1,0,0}, {1,1}},
        Vertex{{  side/2,  -side/2, -side/2},{0,1,0}, {0,0}},
        Vertex{{  side/2,  -side/2,  side/2},{1,1,0}, {1,0}}
    },
    { // Face::Front
        Vertex{{  side/2,   side/2,  side/2},{1,1,0}, {0,1}},
        Vertex{{ -side/2,   side/2,  side/2},{0,0,0}, {1,1}},
        Vertex{{  side/2,  -side/2,  side/2},{0,1,0}, {0,0}},
        Vertex{{ -side/2,  -side/2,  side/2},{1,0,0}, {1,0}}
    },
    { // Face::Back
        Vertex{{ -side/2,   side/2, -side/2},{1,1,0}, {0,1}},
        Vertex{{  side/2,   side/2, -side/2},{0,0,0}, {1,1}},
        Vertex{{ -side/2,  -side/2, -side/2},{0,1,0}, {0,0}},
        Vertex{{  side/2,  -side/2, -side/2},{1,0,0}, {1,0}}
    }
};

FaceIndexData FaceIndices={
    {0,1,2,3,2,1}
};



void BlockRenderer::Initialize(){
    Atlas.Initialize();

    Shaders[0].Create("shaders/block.frag.glsl", GL_FRAGMENT_SHADER);
    Shaders[1].Create("shaders/block.vert.glsl", GL_VERTEX_SHADER);

    VertexAttribute QubeVertexFormat[] = {VertexAttribute::Float3, VertexAttribute::Float3, VertexAttribute::Float2};

    Pipeline.Create({Shaders, sizeof(Shaders)/sizeof(Shader)}, {QubeVertexFormat, sizeof(QubeVertexFormat)/sizeof(VertexAttribute)});

    VertexBuffer.Create(sizeof(StagingVertexBuffer), GPUMemoryTypes::DynamicVRAM);
    IndexBuffer.Create(sizeof(StagingIndexBuffer), GPUMemoryTypes::DynamicVRAM);
    UniformBuffer.Create(sizeof(StagingUnifromBuffer), GPUMemoryTypes::DynamicVRAM);

    Pipeline.Bind();

    glUniform1i(Pipeline.UniformLocation("u_Texture"),0);

}

void BlockRenderer::BeginFrame(const FPSCamera &camera){


    StagingUnifromBuffer.Projection = Transpose(camera.Projection);
    StagingUnifromBuffer.View = Transpose(camera.GetView());
    StagingUnifromBuffer.FOV  = camera.FOV;

    UniformBuffer.UploadData(sizeof(StagingUnifromBuffer), 0, &StagingUnifromBuffer);

    Pipeline.Bind();
    Pipeline.BindUniformBuffer(UniformBuffer, 0);

    BeginBatch();
}

void BlockRenderer::BeginBatch(){
    PendingFacesCount = 0;
}

void BlockRenderer::Draw(const Vector3i &position, Face face, Block block){
    if(PendingFacesCount == MaxFacesCount){
        EndBatch();
        BeginBatch();
    }

    auto block_texture = BlockTextures[(int)block];
    TextureName face_texture;

    switch (face) {
    case Face::Top:
        face_texture = block_texture.Top;
        break; 
    case Face::Bottom:
        face_texture = block_texture.Bottom;
        break;
    case Face::Front:
    case Face::Back:
    case Face::Left:
    case Face::Right:
        face_texture = block_texture.Side;
        break;
    case Face::ElementsCount:
        LogWarn("Enum 'Face' got ElementsCount in switch statement");
    }

    StagingVertexBuffer[PendingFacesCount] = FaceVertexData::Move(FaceVertices[(int)face], position, Atlas.Get(face_texture));
    StagingIndexBuffer[PendingFacesCount] = FaceIndexData::Bias(FaceIndices, PendingFacesCount);
    PendingFacesCount++;
}

RasterizationMode mode = RasterizationMode::TrianglesList;

void BlockRenderer::EndBatch(){
    if(Keyboard::IsKeyPressed(Keyboard::F))
        mode = RasterizationMode::TrianglesList;
    if(Keyboard::IsKeyPressed(Keyboard::M))
        mode = RasterizationMode::LinesList;

    VertexBuffer.UploadData(sizeof(FaceVertexData) * PendingFacesCount, 0, StagingVertexBuffer);
    IndexBuffer.UploadData(sizeof(FaceIndexData) * PendingFacesCount, 0, StagingIndexBuffer);

    Pipeline.DrawElements(mode, VertexBuffer, IndexBuffer, PendingFacesCount * 6);

    glFlush();
}

void BlockRenderer::EndFrame(){
    EndBatch();
}

void BlockRenderer::Finalize(){
    UniformBuffer.Destroy();
    IndexBuffer.Destroy();
    VertexBuffer.Destroy();

    Shaders[0].Destroy();
    Shaders[1].Destroy();

    Atlas.Finalize();
}