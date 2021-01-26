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
#include "mesh.hpp"

constexpr size_t ChunkSizeX = 16;
constexpr size_t ChunkMaxIndexX = ChunkSizeX - 1;
constexpr size_t ChunkSizeY = 16;
constexpr size_t ChunkMaxIndexY = ChunkSizeY - 1;
constexpr size_t ChunkSizeZ = 256;
constexpr size_t ChunkMaxIndexZ = ChunkSizeZ - 1;

struct Chunk{
    Block Blocks[ChunkSizeX][ChunkSizeY][ChunkSizeZ] = {};

    Chunk();

    ~Chunk();

    void Tree(const Vector3i &position);   

    sx_inline const Block &GetBlock(size_t x, size_t y, size_t z)const{
        return Blocks[std::min(x,ChunkSizeX)][std::min(y,ChunkSizeY)][std::min(z,ChunkSizeZ)];
    }

    sx_inline Block &GetBlock(size_t x, size_t y, size_t z){
        return Blocks[std::min(x,ChunkSizeX)][std::min(y,ChunkSizeY)][std::min(z,ChunkSizeZ)];
    }
};

#endif //CHUNK_HPP