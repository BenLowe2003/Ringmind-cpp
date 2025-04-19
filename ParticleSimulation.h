#ifndef PARTICLESIMULATION_H
#define PARTICLESIMULATION_H

#include <vector>
#include "Particle.h"

class ParticleSimulation {
public:
    ParticleSimulation(int num_particles, float delta_time, unsigned int seed, float accretion_prob);
    void run(int steps);

private:
    void integrate();
    void interaction();

    std::vector<Particle> particles;
    size_t number_particles;
    float delta_time;
    float accretion_probability;
};

#endif // PARTICLESIMULATION_H
