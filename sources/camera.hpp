#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "core/math/matrix4.hpp"
#include "core/math/vector3.hpp"
#include "core/math/vector2.hpp"
#include "math.hpp"

using namespace StraitX;

struct Camera{
    Matrix4f Projection;
    Vector3f Position;
    EulerAngles Rotation;

    Matrix4f GetView()const;

    void Move(const Vector3f &offset);

    void Rotate(float pitch, float yaw);

    static Camera Orthographic(int width, int height, int near, int far);

    static Camera Perspective();


};

struct FPSCamera: Camera{
    float FOV = 60;

    FPSCamera(const Camera &camera);

    void MoveY(float offset);

    void MoveXZ(const Vector2f &offset);
};

#endif//CAMERA_HPP