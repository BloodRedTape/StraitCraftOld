#include "world.hpp"


void World::Draw(ChunkRenderer &renderer){
    for(int i = 0; i<WorldSizeX; i++)
        for(int j = 0; j<WorldSizeY; j++)
            renderer.Draw(m_Chunks[i][j], {i,j});
}