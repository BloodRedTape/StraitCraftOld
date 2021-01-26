#ifndef TYPES_HPP
#define TYPES_HPP

#include "core/math/vector3.hpp"
#include "core/math/vector2.hpp"
using namespace StraitX;

struct Vertex{
    Vector3f Position;
    Vector3f Color;
    Vector2f TexCoords;
};

#endif//TYPES_HPP