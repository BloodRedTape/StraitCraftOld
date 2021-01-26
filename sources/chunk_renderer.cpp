#include "chunk_renderer.hpp"

void ChunkRenderer::Initialize(){
    m_BlockRenderer.Initialize();
}

void ChunkRenderer::BeginFrame(const FPSCamera &camera){
    m_BlockRenderer.BeginFrame(camera);
}

void ChunkRenderer::Draw(const Chunk &chunk, const Vector2i &coords){


    //TODO (void)coords;
    for(int k = ChunkMaxIndexZ; k>=0; k--){
        bool clean = true;
        for(int i = 0; i<ChunkSizeX; i++){
            for(int j = 0; j<ChunkSizeY; j++){
                if(chunk.GetBlock(i, j, k) == Block::Air){
                    clean = false;
                    continue;
                }
                Vector3i block_offset = {i + coords.x * ChunkSizeX, k, j + coords.y * ChunkSizeY};
                if(chunk.GetBlock(i,j,k+1) == Block::Air || k == ChunkMaxIndexZ)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Top,     chunk.Data[i][j][k]);
                if(chunk.GetBlock(i,j,k-1) == Block::Air || !k)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Bottom,  chunk.Data[i][j][k]);
                if(chunk.GetBlock(i,j+1,k) == Block::Air || j == ChunkMaxIndexY)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Front,  chunk.Data[i][j][k]);
                if(chunk.GetBlock(i,j-1,k) == Block::Air || !j)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Back,  chunk.Data[i][j][k]);
                if(chunk.GetBlock(i+1,j,k) == Block::Air || i == ChunkMaxIndexX)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Right,  chunk.Data[i][j][k]);
                if(chunk.GetBlock(i-1,j,k) == Block::Air || !i)
                    m_BlockRenderer.Draw(block_offset, BlockRenderer::Face::Left,  chunk.Data[i][j][k]);

                /*
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Top,     chunk.Data[i][j][k]);
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Bottom,  chunk.Data[i][j][k]);
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Left,    chunk.Data[i][j][k]);
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Right,   chunk.Data[i][j][k]);
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Front,   chunk.Data[i][j][k]);
                m_BlockRenderer.Draw({i,k,j}, BlockRenderer::Face::Back,    chunk.Data[i][j][k]);
                */
            }
        }
        //if(clean)break;
    }
}

void ChunkRenderer::EndFrame(){
    m_BlockRenderer.EndFrame();
}

void ChunkRenderer::Finalize(){
    m_BlockRenderer.Finalize();
}