#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include "block_renderer.hpp"
#include "chunk.hpp"


struct ChunkRenderer{
    BlockRenderer m_BlockRenderer;

    void Initialize();

    void BeginFrame(const FPSCamera &camera);

    void Draw(const Chunk &chunk, const Vector2i &coords);

    void EndFrame();

    void Finalize();
};

#endif//CHUNK_RENDERER_HPP