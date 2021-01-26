#ifndef CHUNK_RENDERER_HPP
#define CHUNK_RENDERER_HPP

#include "block_builder.hpp"
#include "chunk.hpp"

Mesh BuildMesh(const Chunk &chunk, const Vector2i &coords);

#endif//CHUNK_RENDERER_HPP