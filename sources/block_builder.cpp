#include "servers/display_server.hpp"
#include "block_builder.hpp"
#include "types.hpp"

FaceVertexData FaceVertexData::Move(const FaceVertexData &face, const Vector3i &position, const Pair<Vector2f,Vector2f> &tex_coords){
    FaceVertexData data = face;
    for(int i = 0; i<4; i++){
        data.Vertices[i].Position += Vector3f(position)*BlockSize;
    }
    data.Vertices[0].TexCoords = {tex_coords.First.x, tex_coords.First.y + tex_coords.Second.y};
    data.Vertices[1].TexCoords = {tex_coords.First.x + tex_coords.Second.x, tex_coords.First.y + tex_coords.Second.y};
    data.Vertices[2].TexCoords = {tex_coords.First.x, tex_coords.First.y};
    data.Vertices[3].TexCoords = {tex_coords.First.x + tex_coords.Second.x, tex_coords.First.y};
    return data;
}

FaceIndexData &FaceIndexData::Bias(u32 face_number){
    for(int i = 0; i<6; i++)
        Indices[i] += 4 * face_number;
    
    return *this;
}

FaceVertexData FaceVertices[(int)BlockFace::ElementsCount]{
    { // Face::Top
        Vertex{{ -BlockSize/2,   BlockSize/2,  BlockSize/2}, {0,1}},
        Vertex{{  BlockSize/2,   BlockSize/2,  BlockSize/2}, {1,1}},
        Vertex{{ -BlockSize/2,   BlockSize/2, -BlockSize/2}, {0,0}},
        Vertex{{  BlockSize/2,   BlockSize/2, -BlockSize/2}, {1,0}}
    },
    { // Face::Bottom
        Vertex{{  BlockSize/2,  -BlockSize/2,  BlockSize/2}, {0,1}},
        Vertex{{ -BlockSize/2,  -BlockSize/2,  BlockSize/2}, {1,1}},
        Vertex{{  BlockSize/2,  -BlockSize/2, -BlockSize/2}, {0,0}},
        Vertex{{ -BlockSize/2,  -BlockSize/2, -BlockSize/2}, {1,0}}
    },
    { // Face::Left
        Vertex{{ -BlockSize/2,   BlockSize/2,  BlockSize/2}, {0,1}},
        Vertex{{ -BlockSize/2,   BlockSize/2, -BlockSize/2}, {1,1}},
        Vertex{{ -BlockSize/2,  -BlockSize/2,  BlockSize/2}, {0,0}},
        Vertex{{ -BlockSize/2,  -BlockSize/2, -BlockSize/2}, {1,0}}
    },
    { // Face::Right
        Vertex{{  BlockSize/2,   BlockSize/2, -BlockSize/2}, {0,1}},
        Vertex{{  BlockSize/2,   BlockSize/2,  BlockSize/2}, {1,1}},
        Vertex{{  BlockSize/2,  -BlockSize/2, -BlockSize/2}, {0,0}},
        Vertex{{  BlockSize/2,  -BlockSize/2,  BlockSize/2}, {1,0}}
    },
    { // Face::Front
        Vertex{{  BlockSize/2,   BlockSize/2,  BlockSize/2}, {0,1}},
        Vertex{{ -BlockSize/2,   BlockSize/2,  BlockSize/2}, {1,1}},
        Vertex{{  BlockSize/2,  -BlockSize/2,  BlockSize/2}, {0,0}},
        Vertex{{ -BlockSize/2,  -BlockSize/2,  BlockSize/2}, {1,0}}
    },
    { // Face::Back
        Vertex{{ -BlockSize/2,   BlockSize/2, -BlockSize/2}, {0,1}},
        Vertex{{  BlockSize/2,   BlockSize/2, -BlockSize/2}, {1,1}},
        Vertex{{ -BlockSize/2,  -BlockSize/2, -BlockSize/2}, {0,0}},
        Vertex{{  BlockSize/2,  -BlockSize/2, -BlockSize/2}, {1,0}}
    }
};


void BuildBlock(const Vector3i &position, BlockFace face, Block block, FaceVertexData &vertex_data, FaceIndexData &index_data){

    auto block_texture = BlockTextures[(int)block];
    TextureName face_texture;

    switch (face) {
    case BlockFace::Top:
        face_texture = block_texture.Top;
        break; 
    case BlockFace::Bottom:
        face_texture = block_texture.Bottom;
        break;
    case BlockFace::Front:
    case BlockFace::Back:
    case BlockFace::Left:
    case BlockFace::Right:
        face_texture = block_texture.Side;
        break;
    case BlockFace::ElementsCount:
        LogWarn("Enum 'Face' got ElementsCount in switch statement");
    }

    vertex_data = FaceVertexData::Move(FaceVertices[(int)face], position, Atlas.Get(face_texture));
    index_data = {0,1,2,3,2,1};
}

