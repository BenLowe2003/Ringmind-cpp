#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES
#include <cmath> // For sqrt

const float G = 6.6743e-11f; // Gravitational constant 
const float central_body_mass = 1E26f; // Mass of the central body
const float central_body_radius = 6E7; // Radius of the central body
const float central_body_density = 687; // Density of the central body

class Vector3D {
public:
    float x, y, z;

    // Constructors
    Vector3D(float inp_x = 0.0f, float inp_y = 0.0f, float inp_z = 0.0f)
        : x(inp_x), y(inp_y), z(inp_z) {
    }

    // Operators
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D& operator+=(const Vector3D& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D& operator-=(const Vector3D& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }


    Vector3D operator*(float scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D operator/(float scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    float dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    float square_norm() const {
        return dot(*this);
    }

    float norm() const {
        return sqrt(dot(*this));
    }

    Vector3D unit() const {
        return *this / norm();
    }

};


class Particle {
public:
    Vector3D position;
    Vector3D velocity;
    Vector3D force;
    float mass;
    float density;
    float radius;
    float roche_limit;

    // Constructor to initialize the particle with position, velocity, and mass (radius is based on ice density)
    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {

            // Random percentage of ice and rock for the density
            float perc = static_cast<float>(rand()) / RAND_MAX;
            density = 917*perc + 2700*(1-perc);
            
            // Calculates an effective radius (for collision detection purposes)
            radius = pow((3*mass/(4*M_PI*density)), 1/3);

            // Calculates Roche limit (fluid limit)
            roche_limit = 2.456 * central_body_radius * pow(central_body_density / density, 1/3);
        }

    void integrate(float dt) {
        position = position + (velocity * dt); // Update position
        Vector3D acceleration = force * (1.0f / mass); // Calculate acceleration
        velocity = velocity + (acceleration * dt); // Update velocity
        force = Vector3D(0.0f, 0.0f, 0.0f); // Reset force to zero vector
    }

	void interaction(size_t i, std::vector<Particle>& particles, float accretion_probability, std::vector<Vector3D*>& positions) {
		for (size_t j = 0; j < particles.size(); j++) {
            // Roche limit check
            if (position.norm() < roche_limit) {
                // Begins creating new particles until total mass has been used up. Minimum mass is 0.1kg for now.
                float total_mass = 0.0f;
                while (total_mass < mass) {
                    // Mass of new particle is random percentage (10-100%) of initial mass
                    float new_mass = mass * pow(0.54 * static_cast<float>(rand()) / (10*RAND_MAX) + 0.46, 3);
                    // New position is randomly offset from the centre of mass
                    Vector3D new_pos = position + Vector3D(radius * static_cast<float>(rand()) / (RAND_MAX), radius * static_cast<float>(rand()) / (10*RAND_MAX), radius * static_cast<float>(rand()) / (10*RAND_MAX));
                    // Creates new particle and adds it to the list
                    particles.emplace_back(new_pos, velocity, new_mass);
                    positions.emplace_back(new_pos);
                    total_mass += new_mass;
                }
                // Removes the current particle from lists
                particles.erase(particles.begin()+i);
                delete positions[i];
                positions.erase(positions.begin()+i);
                
            }
            else {
                // Prevents self-interaction or accreted particle interaction
                if (i != j) {

                    // Gravitational interaction
                    Vector3D r = particles[j].position - position; 
                    float square_distance = r.square_norm();
                    if (square_distance > 0.0f) {

                        force += (r * ((-1.0f) * particles[i].mass * particles[j].mass * G / square_distance * std::sqrt(square_distance)));

                    // Further interactions if particles are in contact
                    if (r.norm() < radius + particles[j].radius){
                        // Accretion of particle j onto particle i
                        // Condition is met if particle j is within the 'effective Hill radius', which is modified by a coefficient depending on the mass difference.
                        float hill_radius = position.norm() * pow(mass/(3*(mass + central_body_mass)), (1/3));
                        float mass_coefficient = 1 + abs(mass - particles[j].mass)/(mass + particles[j].mass);
                        if (r.norm() < hill_radius*mass_coefficient) {
                            // Apply conservation of momentum to find velocity
                            velocity = (velocity * mass + particles[j].velocity * particles[j].mass)/(mass + particles[j].mass);
                            // Sum forces on each particle
                            force += particles[j].force;
                            // Sum masses
                            mass += particles[j].mass;
                            // Sum volumes including a random void percentage between 0% and 10%
                            float volume = 4 / 3 * M_PI * pow(radius, 3) * (1 + static_cast<float>(rand()) / (10*RAND_MAX));
                            float other_volume = 4 / 3 * M_PI * pow(particles[j].radius, 3) * (1 + static_cast<float>(rand()) / (10*RAND_MAX));
                            radius = pow((3 / (4 * M_PI) * (volume + other_volume)), 1/3);
                            density = mass / (volume + other_volume);

                            particles.erase(particles.begin()+j);
                            delete positions[j];
                            positions.erase(positions.begin()+j);
                        }

                        else {
                        // Collisions - formula based on Physics Stack Exchange answer
                        // (https://physics.stackexchange.com/questions/681396/elastic-collision-3d-eqaution)
                            // Normal vector from particle i COM to particle j COM
                            Vector3D n = r.unit();
                            // Reduced mass
                            float m = 1/(1/mass + 1/particles[j].mass);
                            // Impact speed
                            float v_imp = n.dot(velocity - particles[j].velocity);
                            // Velocity change resulting from impulse J = 2mv_imp (coefficient of restitution = 1)
                            velocity -= n * 2*m*v_imp/mass;
                            particles[j].velocity += n * 2*m*v_imp/particles[j].mass;
                        
                        // Viscosity
                            // Exponential coefficient determined using pure water assumption, approximately 100 K temperature in Saturn's ring.
                            float a = -3.05E-15 * density;

                            // W_0 = 0.5 for simplicity, can be adjusted later.
                            force += (particles[j].velocity * particles[j].mass - velocity * mass)/density * 0.5 * pow(M_E, -a*r.square_norm());
                        }
                    }
                }
				}
			}
		}

        // Apply central body force.
		float square_distance = position.square_norm();
		force = force + (position * ((-1.0f) * particles[i].mass * central_body_mass * G / square_distance * std::sqrt(square_distance))); // Apply gravitational force
	}
};

#endif // PARTICLE_H
