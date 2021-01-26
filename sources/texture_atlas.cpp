#include "texture_atlas.hpp"

TextureAtlas Atlas;

constexpr const char *AtlasPath = "resources/texture_atlas.png";

void TextureAtlas::Initialize(){
    Image image;
    image.Create(AtlasPath);
    MainTexture.Create(image);
    image.Destroy();

    MainTexture.Bind(0);

    BlockGrid = Vector2u(image.Width/BlockSize, image.Height/BlockSize);
    BlockEnd = Vector2f(1.0/BlockGrid.x, 1.0/BlockGrid.y);
}

void TextureAtlas::Finalize(){
    MainTexture.Destroy();
}

Pair<Vector2f,Vector2f> TextureAtlas::Get(TextureName tex){
    Vector2u tex_index((u32)tex % BlockGrid.x, (u32)tex/BlockGrid.x);
    return {Vector2f(tex_index.x * BlockEnd.x, tex_index.y * BlockEnd.y), BlockEnd};
}