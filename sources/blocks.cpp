#include "blocks.hpp"

BlockTextureData BlockTextures[(int)Block::BlocksCount]={
    {TextureName::Air},
    {TextureName::GrassTop, TextureName::GrassBottom, TextureName::Grass},
    {TextureName::GrassBottom},
    {TextureName::DiamondBlock},
    {TextureName::EmeraldBlock},
    {TextureName::GoldBlock},
    {TextureName::IronBlock},
    {TextureName::OakLogTop, TextureName::OakLogTop, TextureName::OakLog},
    {TextureName::OakPlanks},
    {TextureName::OakLeaves}
};