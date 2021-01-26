#include "platform/memory.hpp"
#include "world.hpp"
#include "chunk_builder.hpp"

World::World(const Vector2u &size, u64 seed):
    m_Size(size),
    m_Seed(seed)
{
    m_Chunks = (Chunk **)Memory::Alloc(m_Size.x * sizeof(Chunk*));
    for(int i = 0; i<m_Size.x; i++){
        m_Chunks[i] = (Chunk *)Memory::Alloc(m_Size.y * sizeof(Chunk));
        for(int j = 0; j < m_Size.y; j++)
            new (&m_Chunks[i][j]) Chunk;
    }
    
    m_ChunkMeshes = (Mesh **)Memory::Alloc(m_Size.x * sizeof(Mesh*));
    for(int i = 0; i<m_Size.x; i++)
        m_ChunkMeshes[i] = (Mesh *)Memory::Alloc(m_Size.y * sizeof(Mesh));

    LogInfo("Allocated");
    Generate();
    LogInfo("Generated");
}

void World::Generate(){
    for(int i = 0; i<m_Size.x; i++)
    for(int j = 0; j<m_Size.y; j++)
        m_ChunkMeshes[i][j] = BuildMesh(m_Chunks[i][j], {i,j});
}

void World::Render(MeshRenderer &renderer){
    for(int i = 0; i<m_Size.x; i++)
    for(int j = 0; j<m_Size.y; j++){
        renderer.Draw(m_ChunkMeshes[i][j]);
    }
}

World::~World(){
    for(int i = 0; i<m_Size.x; i++)
    for(int j = 0; j<m_Size.y; j++)
        m_ChunkMeshes[i][j].Destroy();

    for(int i = 0; i<m_Size.x; i++)
        Memory::Free(m_ChunkMeshes[i]);
    Memory::Free(m_ChunkMeshes);

    for(int i = 0; i<m_Size.x; i++)
        Memory::Free(m_Chunks[i]);
    Memory::Free(m_Chunks);
}
