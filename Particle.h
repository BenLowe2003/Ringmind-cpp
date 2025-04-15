#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.h"

// Maybe this should be a struct but I'm leaving it as it's own class for now since we may want to introduce further functionality.

class Particle {
public:
    Vector3D position;
    Vector3D velocity;
    Vector3D force;
    float mass;

    // Constructor to initialize the particle with position, velocity, and mass
    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {}


    void integrate(float dt) {
        velocity = velocity + (force / mass * dt);
        position = position + (velocity * dt);
    }
};

#endif // PARTICLE_H
