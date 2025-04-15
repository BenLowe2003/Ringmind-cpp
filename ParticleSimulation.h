#ifndef PARTICLESIMULATION_H
#define PARTICLESIMULATION_H

#include <vector>
#include "Particle.h"
#include <cstdlib> 

class ParticleSimulation {
public:
    // System Variables
    std::vector<Particle> particles;
    
    // Simulation Parameters
    size_t number_particles;
    float delta_time;
    
    // Initialize Simulation
    ParticleSimulation(int num_particles, float delta_time, float central_mass, float seed);

    // Global Functions
    void run(int steps);
    void update_system(float delta_time);
    void evaluate_momentum(int i);
    
};

#endif 
