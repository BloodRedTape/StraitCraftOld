#include "chunk_builder.hpp"
#include "block_builder.hpp"

Mesh BuildMesh(const Chunk &chunk, const Vector2i &coords){
    std::vector<FaceVertexData> StagingVertexData;
    std::vector<FaceIndexData>  StagingIndexData;

    for(int k = 0; k<ChunkSizeZ; k++)
    for(int j = 0; j<ChunkSizeY; j++)
    for(int i = 0; i<ChunkSizeX; i++){
        if(chunk.GetBlock(i, j, k) == Block::Air)continue;

        Vector3i block_offset = {i + coords.x * ChunkSizeX, k, j + coords.y * ChunkSizeY};
        FaceVertexData vert;
        FaceIndexData ind;
        if(chunk.GetBlock(i,j,k+1) == Block::Air || k == ChunkMaxIndexZ){
            BuildBlock(block_offset, BlockFace::Top, chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
        if(chunk.GetBlock(i,j,k-1) == Block::Air || !k){
            BuildBlock(block_offset, BlockFace::Bottom,  chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
        if(chunk.GetBlock(i,j+1,k) == Block::Air || j == ChunkMaxIndexY){
            BuildBlock(block_offset, BlockFace::Front,  chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
        if(chunk.GetBlock(i,j-1,k) == Block::Air || !j){
            BuildBlock(block_offset, BlockFace::Back,  chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
        if(chunk.GetBlock(i+1,j,k) == Block::Air || i == ChunkMaxIndexX){
            BuildBlock(block_offset, BlockFace::Right,  chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
        if(chunk.GetBlock(i-1,j,k) == Block::Air || !i){
            BuildBlock(block_offset, BlockFace::Left,  chunk.Blocks[i][j][k], vert, ind);
            StagingVertexData.push_back(vert);
            StagingIndexData.push_back(ind.Bias(StagingIndexData.size()));
        }
    }
    Mesh mesh;
    mesh.Create(StagingVertexData.data(),StagingVertexData.size() * 4 * sizeof(Vertex),(u32*)StagingIndexData.data(),StagingIndexData.size() * 6 * sizeof(u32));
    return mesh;
}
