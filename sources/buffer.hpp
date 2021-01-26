#ifndef BUFFER_HPP
#define BUFFER_HPP


#include "platform/opengl.hpp"
#include "platform/types.hpp"

enum class GPUMemoryTypes{
    VRAM,
    DynamicVRAM
};

struct Buffer{
    u32 Id = 0;

    void Create(size_t size, GPUMemoryTypes type){
        glGenBuffers(1, &Id);
        glBindBuffer(GL_COPY_WRITE_BUFFER, Id);
        glBufferData(GL_COPY_WRITE_BUFFER, size, nullptr, type == GPUMemoryTypes::VRAM ? GL_STATIC_DRAW : GL_DYNAMIC_COPY);
    }

    void Destroy(){
        glDeleteBuffers(1, &Id);
    }

    void UploadData(size_t size, size_t offset, void *data){
        glBindBuffer(GL_COPY_WRITE_BUFFER, Id);
        glBufferSubData(GL_COPY_WRITE_BUFFER, offset, size, data);
    }
};


#endif //BUFFER_HPP