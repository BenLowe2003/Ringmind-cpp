#include "ParticleSimulation.h"   // Include the header for this class
#include <iostream>               // For console output
#include <cstdlib>                // For rand() and srand()

// Constructor: initializes the simulation with num_particles particles,
// a given time step (dt), and a random seed.
ParticleSimulation::ParticleSimulation(int num_particles, float dt, float seed)
    : number_particles(num_particles), delta_time(dt) {

    srand(seed); // Seed the random number generator

    // Generate particles with random positions and velocities
    for (size_t i = 0; i < number_particles; ++i) {
        // Random position in [0, 1)
        Vector3D pos(static_cast<float>(rand()) / RAND_MAX,
                     static_cast<float>(rand()) / RAND_MAX,
                     static_cast<float>(rand()) / RAND_MAX);
        
        // Random velocity in [-0.5, 0.5)
        Vector3D vel(
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            static_cast<float>(rand()) / RAND_MAX - 0.5f,
            static_cast<float>(rand()) / RAND_MAX - 0.5f
        );

        float m = 1.0f; // Set mass (currently unused)

        // Create and store the particle in the list
        particles.emplace_back(pos, vel, m);
    }
}

// Runs the simulation for a number of time steps
void ParticleSimulation::run(int steps) {
    for (int step = 0; step < steps; ++step) {
        // Update all particles' positions
        for (size_t i = 0; i < particles.size(); ++i) {
            integrate(i);
        }

        // Print out the position of the first particle every 20 steps
        if (step % 20 == 0) {
            std::cout << "Step " << step << ": Particle 0 position = ("
                      << particles[0].position.x << ", "
                      << particles[0].position.y << ", "
                      << particles[0].position.z << ")\n";
        }
    }
}

// Simple integrator: moves particle i based on its velocity and time step
void ParticleSimulation::integrate(int i) {
    particles[i].position = particles[i].position + particles[i].velocity * delta_time;
}
