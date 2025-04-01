#include "ParticleSimulation.h"
#include <iostream>
#include <cstdlib>

ParticleSimulation::ParticleSimulation(int num_particles, float dt, float seed)
    : number_particles(num_particles), delta_time(dt) {
    
    srand(seed);

    for (size_t i = 0; i < number_particles; ++i) {
        Vector3D pos(static_cast<float>(rand()) / RAND_MAX,
                     static_cast<float>(rand()) / RAND_MAX,
                     static_cast<float>(rand()) / RAND_MAX);
        Vector3D vel(
    		static_cast<float>(rand()) / RAND_MAX - 0.5f,
    		static_cast<float>(rand()) / RAND_MAX - 0.5f,
    		static_cast<float>(rand()) / RAND_MAX - 0.5f
	);

        float m = 1.0f;

        particles.emplace_back(pos, vel, m);
    }
}

void ParticleSimulation::run(int steps) {
    for (int step = 0; step < steps; ++step) {
        for (size_t i = 0; i < particles.size(); ++i) {
            integrate(i);
        }

        if (step % 20 == 0) {
            std::cout << "Step " << step << ": Particle 0 position = ("
                      << particles[0].position.x << ", "
                      << particles[0].position.y << ", "
                      << particles[0].position.z << ")\n";
        }
    }
}


void ParticleSimulation::integrate(int i) {
    particles[i].position = particles[i].position + particles[i].velocity * delta_time;
}
