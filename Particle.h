#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec3.h"

// Maybe this should be a struct but I'm leaving it as it's own class for now since we may want to introduce further functionality.

class Particle {
public:
    Vec3 position;
    Vec3 velocity;
    float mass;

    // Constructor to initialize the particle with position, velocity, and mass
    Particle(const Vec3& pos = Vec3(), const Vec3& vel = Vec3(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {}

};

#endif // PARTICLE_H
