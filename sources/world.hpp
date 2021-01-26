#ifndef WORLD_HPP
#define WORLD_HPP

#include "platform/types.hpp"
#include "chunk.hpp"
#include "mesh_renderer.hpp"

class World{
private:
    const Vector2u m_Size = {0, 0};
    Chunk **m_Chunks = nullptr;
    Mesh **m_ChunkMeshes = nullptr;
    u64 m_Seed = 0;
public:
    World(const Vector2u &size, u64 seed);

    void Generate();

    void Render(MeshRenderer &renderer);

    ~World();

};

#endif//WORLD_HPP