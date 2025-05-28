#ifndef PARTICLESIMULATION_H
#define PARTICLESIMULATION_H

#include <vector>
#include "Particle.h"

constexpr size_t number_particles = 500; // Number of particles in the simulation

class ParticleSimulation {
public:

    ParticleSimulation(float delta_time, unsigned int seed, float accretion_prob);
    void run(int steps);
    void UpdatePositions();
    float positions[3 * number_particles];

private:
    void integrate();
    void interaction();

    

    std::vector<Particle> particles;
    float delta_time;
    float accretion_probability;
};



#endif 
