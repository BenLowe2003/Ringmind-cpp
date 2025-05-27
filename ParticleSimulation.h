#ifndef PARTICLESIMULATION_H
#define PARTICLESIMULATION_H

#include <vector>
#include "Particle.h"

constexpr size_t number_particles = 1000; // Number of particles in the simulation

class ParticleSimulation {
public:

    ParticleSimulation(float delta_time, unsigned int seed, float accretion_prob);

    void run(int steps);

private:
    void integrate();
    void interaction();

	float positions[3 * number_particles]; // Array to store particle positions
	float velocities[3 * number_particles]; // Array to store particle velocities
	float forces[3 * number_particles]; // Array to store particle forces
	float masses[number_particles]; // Array to store particle masses

    std::vector<Particle> particles;
    size_t number_particles;
    float delta_time;
    float accretion_probability;
};



#endif 
