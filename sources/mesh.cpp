#include "mesh.hpp"


void Mesh::Create(void *vertex_data, size_t vsize, u32 *index_data, size_t isize){
    ElementsCount = isize / sizeof(u32);
    VertexBuffer.Create(vsize, GPUMemoryTypes::VRAM);
    VertexBuffer.UploadData(vsize, 0, vertex_data);

    IndexBuffer.Create(isize, GPUMemoryTypes::VRAM);
    IndexBuffer.UploadData(isize, 0, index_data);
}

void Mesh::Destroy(){
    IndexBuffer.Destroy();
    VertexBuffer.Destroy();
}