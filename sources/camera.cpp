#include "camera.hpp"
#include "math.hpp"

Matrix4f Camera::GetView()const{
    Matrix4f matrix;
    matrix[0][3] = Position.x;
    matrix[1][3] = Position.y;
    matrix[2][3] = Position.z;
    matrix[3][3] = 1;

    return Rotation.GetRotor()*matrix;
}

void Camera::Move(const Vector3f &offset){
    Position -= offset;//offset.x*Vector3f(cos(rad(-Rotation.Yaw)), 0, sin(rad(Rotation.Yaw))) + offset.z*Vector3f(-sin(rad(Rotation.Yaw)), 0, cos(rad(Rotation.Yaw)));
}

void Camera::Rotate(float pitch, float yaw){
    if(Rotation.Pitch + pitch < 90 && Rotation.Pitch + pitch > -90)
        Rotation.Rotate(pitch, yaw, 0);
}

Camera Camera::Orthographic(int width, int height, int near, int far){

    float unit = far-near;
    Camera camera;
    camera.Projection[0][0] = 2.f/width;
    camera.Projection[1][1] = 2.f/height;
    camera.Projection[2][2] = 1.f/unit;
    camera.Projection[2][3] = -near/unit;
    camera.Projection[3][3] = 1;
    return camera;
}

Camera Camera::Perspective(){
    return {};
}


FPSCamera::FPSCamera(const Camera &camera):
    Camera(camera)
{}

void FPSCamera::MoveY(float offset){
    Move({0, offset, 0});
}

void FPSCamera::MoveXZ(const Vector2f &offset){
    Move(offset.x * Vector3f(cos(rad(-Rotation.Yaw)), 0, sin(rad(-Rotation.Yaw))) + offset.y * Vector3f(-sin(rad(-Rotation.Yaw)), 0, cos(rad(-Rotation.Yaw))));
}