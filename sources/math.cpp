#include "math.hpp"


EulerAngles::EulerAngles(float pitch, float yaw, float roll):
    Pitch(pitch), Yaw(yaw), Roll(roll)
{}

void EulerAngles::Rotate(float pitch, float yaw, float roll){
    Pitch += pitch;
    Yaw   += yaw;
    Roll  += roll;
}

Matrix4f EulerAngles::GetRotorPitch()const{
    Matrix4f p;
    p[1][1] =  cos(rad(Pitch));
    p[2][1] =  sin(rad(Pitch));
    p[1][2] = -sin(rad(Pitch));
    p[2][2] =  cos(rad(Pitch));
    return p;
}
Matrix4f EulerAngles::GetRotorYaw()const{
    Matrix4f y;
    y[0][0] =  cos(rad(Yaw));
    y[2][0] =  sin(rad(Yaw));
    y[0][2] = -sin(rad(Yaw));
    y[2][2] =  cos(rad(Yaw));
    return y;
}

Matrix4f EulerAngles::GetRotorRoll()const{
    Matrix4f r;
    r[0][0] =  cos(rad(Roll));
    r[1][0] =  sin(rad(Roll));
    r[0][1] = -sin(rad(Roll));
    r[1][1] =  cos(rad(Roll));
    return r;
}

Matrix4f EulerAngles::GetRotor()const{
    return GetRotorPitch()*GetRotorYaw()*GetRotorRoll();
}