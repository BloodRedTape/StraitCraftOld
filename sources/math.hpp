#ifndef MATH_HPP 
#define MATH_HPP 

#include "core/math/matrix4.hpp"
#include <cmath>

using namespace StraitX;

sx_inline double rad(double degree){
    return degree/180*M_PI;
}

template <typename T>
Matrix4<T> Transpose(const Matrix4<T> &matrix){
    Matrix4<T> result = matrix;
    result[0][1] = matrix[1][0];
    result[0][2] = matrix[2][0];
    result[0][3] = matrix[3][0];
    result[1][0] = matrix[0][1];
    result[1][2] = matrix[2][1];
    result[1][3] = matrix[3][1];
    result[2][0] = matrix[0][2];
    result[2][1] = matrix[1][2];
    result[2][3] = matrix[3][2];
    result[3][0] = matrix[0][3];
    result[3][1] = matrix[1][3];
    result[3][2] = matrix[2][3];
    return result;
}

template <typename T>
Matrix4<T> operator*(const Matrix4<T> &l,const Matrix4<T> &r){
    Matrix4<T> result;
    for(int i = 0; i<4; i++){
        for(int j = 0; j<4; j++){
            result[i][j]=l[i][0]*r[0][j]+l[i][1]*r[1][j]+l[i][2]*r[2][j]+l[i][3]*r[3][j];
        }
    }
    return result;
}


struct EulerAngles{
    float Pitch = 0, Yaw = 0, Roll = 0;

    EulerAngles() = default;

    EulerAngles(float pitch, float yaw, float roll);

    void Rotate(float pith, float yaw, float roll);

    Matrix4f GetRotorPitch()const;

    Matrix4f GetRotorYaw()const;

    Matrix4f GetRotorRoll()const;

    Matrix4f GetRotor()const;
};

#endif//MATH_HPP 