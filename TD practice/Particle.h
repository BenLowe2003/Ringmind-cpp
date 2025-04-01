#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"

class Particle {
public:
    Vector3D position;
    Vector3D velocity;
    float mass;

    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {}
};

#endif // PARTICLE_H
