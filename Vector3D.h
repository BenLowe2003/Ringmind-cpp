#ifndef Vector3D_H
#define Vector3D_H

#include <cmath>
#include <iostream>

class Vector3D {
public:
    float x, y, z;

    // Constructors
    Vector3D(float inp_x = 0.0f, float inp_y = 0.0f, float inp_z = 0.0f)
        : x(inp_x), y(inp_y), z(inp_z) {}

    // Operators
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

        Vector3D& operator+=(const Vector3D& other)
        {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
        }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

        Vector3D& operator-=(const Vector3D& other)
        {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
        }


    Vector3D operator*(float scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator/(float scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    float dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float square_norm() const {
        return dot(*this);
    }

    float norm() const {
        return sqrt(dot(*this));
    }

    Vector3D unit() const{
        return *this / norm();
    }

};

#endif // Vector3D_H
