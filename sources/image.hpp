#ifndef IMAGE_HPP
#define IMAGE_HPP

#include "core/math/vector2.hpp"
#include "core/log.hpp"
#include "stb_image.h"
using namespace StraitX;

struct Image{
    int Width  = 0;
    int Height = 0;
    i32 BPP    = 0;
    u8 *Pixels = nullptr;

    void Create(const char *filename){
        stbi_set_flip_vertically_on_load(true);
        Pixels = stbi_load(filename, &Width, &Height,&BPP,4);
        if(!Pixels)
            LogError("Image: Can't load '%' ", filename);
    }

    void Destroy(){
        stbi_image_free(Pixels);
    }
};

#endif//IMAGE_HPP