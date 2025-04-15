#include <iostream>
#include "ParticleSimulation.h"
#include <ctime>   // For seeding randomness
    

int main() {
    // Create a simulation with 1000 particles
    int seed = static_cast<unsigned int>(time(0));
    ParticleSimulation sim(2, 0.5, seed);

    // Run the simulation
    sim.run(1000);

    return 0;
}
