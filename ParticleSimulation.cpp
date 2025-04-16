#include "ParticleSimulation.h" // Include the particle simulation Class
#include "Particle.h"         // Include the particle Class
#include <iostream>               // For console output
#include <cstdlib>                // For rand() and srand()



// Constructor: initializes the simulation with num_particles particles,
// a given time step (dt), and a random seed.
ParticleSimulation::ParticleSimulation(int num_particles, float dt, unsigned int seed)
    : number_particles(num_particles), delta_time(dt) {

    srand(seed); // Seed the random number generator

    // Generate particles with random positions and velocities
    for (size_t i = 0; i < number_particles; ++i) {
		// Random distance and angle for spherical coordinates
		float r = static_cast<float>(rand()) / RAND_MAX * 50.0f + 10.0f; // Random distance in [10, 60)
		float theta = static_cast<float>(rand()) / RAND_MAX * 2.0f * M_PI; // Random angle in [0, 2π)
		float phi = static_cast<float>(rand()) / RAND_MAX * M_PI; // Random angle in [0, π)

		// Convert spherical coordinates to Cartesian coordinates
		float x = r * sin(phi) * cos(theta);
		float y = r * sin(phi) * sin(theta);
		float z = r * cos(phi);

		// Create a Vector3D object for the position
		Vector3D pos(x, y, z);

		// Find orbital velocity
		float v = sqrt(G * central_body_mass / r); // Orbital velocity
		float vx = -v * sin(theta);
		float vy = v * cos(theta);
		float vz = 0.0f; // Assuming motion in the xy-plane

		// Create a Vector3D object for the velocity
		Vector3D vel(vx, vy, vz);

        float m = 1.0f; // Set mass (currently unused)

		// Print particles information
		std::cout << "Particle " << i << ": Position = ("
			<< pos.x << ", " << pos.y << ", " << pos.z << "), "
			<< "Velocity = (" << vel.x << ", " << vel.y << ", " << vel.z << ")\n";

        // Create and store the particle in the list
        particles.emplace_back(pos, vel, m);
    }
}

// Runs the simulation for a number of time steps
void ParticleSimulation::run(int steps) {
    for (int step = 0; step < steps; ++step) {
        
		interaction(); // Update forces based on interactions

        // Print out the position of the first particle every 20 steps
        if (step % 20 == 0) {
			for (int i = 0; i < number_particles; i++) {
				std::cout << "Step " << step << ": Particle " << i << " position = ("
					<< particles[i].position.x << ", "
					<< particles[i].position.y << ", "
					<< particles[i].position.z << ") "
					<< "Velocity = ("
					<< particles[i].velocity.x << ", "
					<< particles[i].velocity.y << ", "
					<< particles[i].velocity.z << ")\n";
			}
        }
        // Update all particles' positions
        integrate();
    }
}

// Simple integrator: moves particle i based on its velocity and time step
void ParticleSimulation::integrate() {
    for (int i = 0; i <  number_particles; i++){
        particles[i].integrate(delta_time);
    }
}

void ParticleSimulation::interaction() {
    for (int i = 0; i < number_particles; i++) {
		particles[i].interaction(i, particles);
    }
}
