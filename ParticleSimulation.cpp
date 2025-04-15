#include "ParticleSimulation.h"   // Include the header for this class
#include <iostream>               // For console output
#include <cstdlib>                // For rand() and srand()

// Constructor: initializes the simulation with num_particles particles,
// a given time step (dt), and a random seed.
ParticleSimulation::ParticleSimulation(int num_particles, float dt, float central_mass, float seed)
    : number_particles(num_particles), delta_time(dt) {

    srand(seed); // Seed the random number generator

    // Generate high-mass central particle (i.e. planet)
    Vector3D pos(0, 0, 0);
    Vector3D vel(0, 0, 0);
    particles.emplace_back(Vector3D(0,0,0), Vector3D(0,0,0), central_mass);

    // Generate particles with random positions and velocities
    for (size_t i = 0; i < number_particles; ++i) {
        // Random radial distance in Mm, between 0 Mm and 10 Mm
        float r = static_cast<float>(rand() / RAND_MAX * 10);
        // Converts to metres
        r *= 1E6;

        // Random polar angle, in radians, between 0 and 2pi
        float phi = static_cast<float>(rand() / RAND_MAX * 2 * 3.14159);

        // Random azimuthal angle, in radians, between 0 and pi
        float theta = static_cast<float>(rand() / RAND_MAX * 3.14159);

        // Converts to Cartesian and generates position vector
        Vector3D pos(r * std::sin(theta) * std::cos(phi),
                     r * std::sin(theta) * std::sin(phi),
                     r * std::cos(phi)                     
                    );
        
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

        // Zero all particle forces
        for (Particle particle : particles){
            particle.force = Vector3D();
        }

        // Calculate acceleration of all particles
        for (size_t i = 0; i < particles.size(); ++i) {

            for (size_t j = i+1; j < particles.size(); ++j){
                    
                    // Temporary force variable
                    Vector3D* force = new Vector3D;

                    // Force exterted on i by j
                    *force += (particles[i].position - particles[j].position).unit() * 6.6743E-11 * 
                                           particles[i].mass * particles[j].mass  / 
                                           (particles[i].position - particles[j].position).square_norm();
                    
                    // Check force is finite
                    if (!std::isnan((*force).x)) {
                        // Apply forces using symmetry
                        particles[i].force += *force;
                        particles[j].force -= *force;
                    }
                    
                    // Deallocate memory
                    delete force;
                    force = nullptr;
                
            } 
    
        }
        
        // Update all particles' positions and velocities
        for (size_t i = 0; i < particles.size(); ++i) {
            particles[i].integrate(delta_time);
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