#ifndef WORLD_HPP
#define WORLD_HPP

#include "platform/types.hpp"
#include "chunk.hpp"
#include "chunk_renderer.hpp"

constexpr size_t WorldSizeX = 4;
constexpr size_t WorldSizeY = 4;

class World{
private:
    Chunk m_Chunks[WorldSizeX][WorldSizeY];
public:

    void Draw(ChunkRenderer &renderer);

};

#endif//WORLD_HPP