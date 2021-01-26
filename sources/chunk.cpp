#include "chunk.hpp"

static_assert((int)Block::Air==0, "air is not zero");

Chunk::Chunk(){
    Memory::Set(Blocks, (int)Block::Air, sizeof(Blocks));
    for(int i = 0; i<ChunkSizeX; i++){
        for(int j = 0; j<ChunkSizeY; j++)
        {
            size_t height = 20;
            Blocks[i][j][height] = Block::Grass;
            if(rand()%40 == 3)
                Tree({i,j,height+1});
            Blocks[i][j][0] = Block::Bedrock;
            for(int k = 1; k<std::min(height, ChunkSizeZ); k++){
                if(k < height - 2)
                    if(rand()%40 == 2 && k < 5)
                        Blocks[i][j][k] = Block::DiamondOre;
                    else if(rand()%40 == 5)
                        Blocks[i][j][k] = Block::IronOre;
                    else if(rand()%40 == 8 && k < 8)
                        Blocks[i][j][k] = Block::GoldOre;
                    else if(rand()%80 == 8 && k < 8)
                        Blocks[i][j][k] = Block::EmeraldOre;
                    else if(rand()%20 == 5)
                        Blocks[i][j][k] = Block::CoalOre;
                    else
                        Blocks[i][j][k] = Block::Stone;
                else
                    Blocks[i][j][k] = Block::Dirt;
            }
        }
    }
}

Chunk::~Chunk(){
}


void Chunk::Tree(const Vector3i &position){
    Block Leaves = Block::OakLeaves;

    if(rand() % 70 == 3)
        Leaves = Block::Emerald;

    GetBlock(position.x,   position.y,   position.z+0) = Block::OakLog;
    GetBlock(position.x,   position.y,   position.z+1) = Block::OakLog;
    GetBlock(position.x,   position.y,   position.z+2) = Block::OakLog;
    GetBlock(position.x,   position.y+1, position.z+2) = Leaves;
    GetBlock(position.x,   position.y-1, position.z+2) = Leaves;
    GetBlock(position.x+1, position.y,   position.z+2) = Leaves;
    GetBlock(position.x-1, position.y,   position.z+2) = Leaves;
    GetBlock(position.x+1, position.y+1, position.z+2) = Leaves;
    GetBlock(position.x+1, position.y-1, position.z+2) = Leaves;
    GetBlock(position.x-1, position.y+1, position.z+2) = Leaves;
    GetBlock(position.x-1, position.y-1, position.z+2) = Leaves;
    GetBlock(position.x,   position.y,   position.z+3) = Leaves;
    GetBlock(position.x,   position.y+1, position.z+3) = Leaves;
    GetBlock(position.x,   position.y-1, position.z+3) = Leaves;
    GetBlock(position.x+1, position.y,   position.z+3) = Leaves;
    GetBlock(position.x-1, position.y,   position.z+3) = Leaves;
}   