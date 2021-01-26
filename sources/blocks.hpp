#ifndef BLOCKS_HPP
#define BLOCKS_HPP

#include "texture_atlas.hpp"

enum class Block: u8{
    Air = 0,
    Grass,
    Dirt,
    Diamond,
    Emerald,
    Gold,
    Iron,

    OakLog,
    OakPlanks,

    OakLeaves,

    DiamondOre,
    EmeraldOre,
    GoldOre,
    IronOre,
    Cobblestone,
    Stone,
    CoalOre,

    Bedrock,

    BlocksCount
};

struct BlockTextureData{
    TextureName Top;
    TextureName Bottom;
    TextureName Side;

    BlockTextureData(TextureName all):
        Top(all),
        Bottom(all),
        Side(all)
    {}

    BlockTextureData(TextureName top, TextureName bottom, TextureName side):
        Top(top),
        Bottom(bottom),
        Side(side)
    {}
};

extern BlockTextureData BlockTextures[(int)Block::BlocksCount];

#endif//BLOCKS_HPP