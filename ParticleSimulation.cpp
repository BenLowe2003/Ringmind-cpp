#include "ParticleSimulation.h" // Include the particle simulation Class
#include "Particle.h"         // Include the particle Class
#include <iostream>               // For console output
#include <cstdlib>                // For rand() and srand()



// Constructor: initializes the simulation with num_particles particles,
// a given time step (dt), and a random seed.
ParticleSimulation::ParticleSimulation(float dt, unsigned int seed, float accretion_prob)
	: delta_time(dt), accretion_probability(accretion_prob) {

	srand(seed); // Seed the random number generator

	// Generate particles with random positions and velocities
	for (size_t i = 0; i < number_particles; ++i) {
		// Create and store the particle in the list
		Particle particle = Particle();
		particles.push_back(particle);
	}
}

// Simple integrator: moves particle i based on its velocity and time step
void ParticleSimulation::integrate() {
	
	for (size_t i = 0; i < number_particles; i++) {
		particles[i].integrate(delta_time);
		
	}
}

void ParticleSimulation::interaction() {
	
	for (size_t i = 0; i < number_particles; i++) {
		particles[i].interaction(i, particles, accretion_probability);
	}
}

// Runs the simulation for a number of time steps
void ParticleSimulation::run(int steps) {
	for (int step = 0; step < steps; ++step) {
		
		interaction(); // Update forces based on interactions
		integrate();
	}
}



float example_positions[8 * 3] = {
		0.5f, 0.5f, 0.5f
		, -0.5f, 0.5f, 0.5f
		, -0.5f, -0.5f, 0.5f
		, 0.5f, -0.5f, 0.5f
		, 0.5f, 0.5f, -0.5f
		, -0.5f, 0.5f, -0.5f
		, -0.5f, -0.5f, -0.5f
		, 0.5f, -0.5f, -0.5f
};

void ParticleSimulation::UpdatePositions() {
	const float scale = 0.0000000001f;
	for (size_t i = 0; i < number_particles; i++) {
		positions[3 * i] = particles[i].position.x * scale_factor;
		positions[3 * i + 1] = particles[i].position.y * scale_factor;
		positions[3 * i + 2] = particles[i].position.z * scale_factor;
	}

	for (int i = 0; i < 8 * 3; i++) {
		positions[i] *= example_positions[i];
	}
}
