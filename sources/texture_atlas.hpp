#ifndef TEXTURE_ATLAS_HPP
#define TEXTURE_ATLAS_HPP

#include "texture.hpp"
#include "core/pair.hpp"

enum class TextureName: u8{
    Air = 0,
    Grass,
    GrassTop,
    GrassBottom,

    DiamondBlock,
    EmeraldBlock,
    GoldBlock,
    IronBlock,

    OakLog,
    OakLogTop,
    OakPlanks,

    OakLeaves,
    
    ElementsCount
};

struct TextureAtlas{
    static constexpr size_t BlockSize = 16;

    Vector2u BlockGrid = {};
    Vector2f BlockEnd = {};
    Texture MainTexture;

    void Initialize();

    void Finalize();

    Pair<Vector2f,Vector2f> Get(TextureName tex);
};

#endif //TEXTURE_ATLAS_HPP