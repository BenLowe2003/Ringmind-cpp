#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"

// Maybe this should be a struct but I'm leaving it as it's own class for now since we may want to introduce further functionality.

class Particle {
public:
    Vector3D position;
    Vector3D velocity;
    float mass;

    // Constructor to initialize the particle with position, velocity, and mass
    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {}

};

#endif // PARTICLE_H
