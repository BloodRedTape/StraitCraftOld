#ifndef CHUNK_HPP
#define CHUNK_HPP

#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include "platform/types.hpp"
#include "core/math/vector3.hpp"
#include "buffer.hpp"
#include "blocks.hpp"
#include "block_renderer.hpp"

constexpr size_t ChunkSizeX = 16;
constexpr size_t ChunkMaxIndexX = ChunkSizeX - 1;
constexpr size_t ChunkSizeY = 16;
constexpr size_t ChunkMaxIndexY = ChunkSizeY - 1;
constexpr size_t ChunkSizeZ = 256;
constexpr size_t ChunkMaxIndexZ = ChunkSizeZ - 1;

struct Chunk{
    Block Data[ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {};
    Buffer VertexBuffer;
    Buffer IndexBuffer;

    std::vector<FaceVertexData> StagingVertexBuffer{32};
    std::vector<FaceIndexData>  StagingIndexBuffer {32};
    u32 FacesCount = 0;

    Chunk(){
        for(int i = 0; i<ChunkSizeX; i++){
            for(int j = 0; j<ChunkSizeY; j++)
            {
                size_t height = 20;
                Data[i][j][height] = Block::Grass;
                if(rand()%40 == 3)
                    Tree({i,j,height+1});
                Data[i][j][0] = Block::Bedrock;
                for(int k = 1; k<std::min(height, ChunkSizeZ); k++){
                    if(k < height - 2)
                        if(rand()%40 == 2 && k < 5)
                            Data[i][j][k] = Block::DiamondOre;
                        else if(rand()%40 == 5)
                            Data[i][j][k] = Block::IronOre;
                        else if(rand()%40 == 8 && k < 8)
                            Data[i][j][k] = Block::GoldOre;
                        else if(rand()%80 == 8 && k < 8)
                            Data[i][j][k] = Block::EmeraldOre;
                        else if(rand()%20 == 5)
                            Data[i][j][k] = Block::CoalOre;
                        else
                            Data[i][j][k] = Block::Stone;
                    else
                        Data[i][j][k] = Block::Dirt;
                }
            }
        }


    }

    void Traverse(){

    }

    ~Chunk(){
        VertexBuffer.Destroy();
        IndexBuffer.Destroy();
    }


    void Tree(const Vector3i &position){
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

    sx_inline const Block &GetBlock(size_t x, size_t y, size_t z)const{
        return Data[std::min(x,ChunkSizeX)][std::min(y,ChunkSizeY)][std::min(z,ChunkSizeZ)];
    }

    sx_inline Block &GetBlock(size_t x, size_t y, size_t z){
        return Data[std::min(x,ChunkSizeX)][std::min(y,ChunkSizeY)][std::min(z,ChunkSizeZ)];
    }
};

#endif //CHUNK_HPP