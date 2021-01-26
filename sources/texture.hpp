#ifndef TEXTURE_HPP 
#define TEXTURE_HPP 

#include "image.hpp"
#include "platform/types.hpp"
#include "platform/opengl.hpp"
#include "debug.hpp"

using namespace StraitX;

struct Texture{
    u32 Id = 0;

    void Create(const Image &image){
        GL(glGenTextures(1, &Id));
        GL(glBindTexture(GL_TEXTURE_2D, Id));
        GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.Width, image.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.Pixels));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    }

    void Bind(u32 slot){
        glBindTextureUnit(slot, Id);
    }

    void Destroy(){
        glDeleteTextures(1, &Id);
    }
};

#endif //TEXTURE_HPP 