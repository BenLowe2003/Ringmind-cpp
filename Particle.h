#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES
#include <cmath> // For sqrt

const float G = 6.6743e-11f; // Gravitational constant 
const float central_body_mass = 100.0f; // Mass of the central body

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
    float radius;
    bool accreted;

    // Constructor to initialize the particle with position, velocity, and mass (radius is based on ice density)
    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f, float r = 0.62f)
        : position(pos), velocity(vel), mass(m), radius(r) {accreted = false;}

    void integrate(float dt) {
        position = position + (velocity * dt); // Update position
        Vector3D acceleration = force * (1.0f / mass); // Calculate acceleration
        velocity = velocity + (acceleration * dt); // Update velocity
        force = Vector3D(0.0f, 0.0f, 0.0f); // Reset force to zero vector
    }

	void interaction(size_t i, std::vector<Particle>& particles, float accretion_probability) {
		for (size_t j = 0; j < particles.size(); j++) {
            // Prevents self-interaction or accreted particle interaction
			if (i != j && !particles[j].accreted)  {
                // Gravitational interaction
				Vector3D r = particles[j].position - position; 
				float square_distance = r.square_norm();
				if (square_distance > 0.0f) {

					force += (r * ((-1.0f) * particles[i].mass * particles[j].mass * G / square_distance * std::sqrt(square_distance)));

                if (r.norm() < radius + particles[j].radius){
                    // Accretion with random probability, keeps position of particle i but with increased mass
                    if (static_cast<float>(rand()) / RAND_MAX < accretion_probability) {
                        // Apply conservation of momentum to find velocity
                        velocity = (velocity * mass + particles[j].velocity * particles[j].mass)/(mass + particles[j].mass);
                        // Sum forces on each particle
                        force += particles[j].force;
                        // Sum masses
                        mass += particles[j].mass;
                        // Sum volumes to find new radius (assume still spherical)
                        float volume = 4 / 3 * M_PI * pow(radius, 3);
                        float other_volume = 4 / 3 * M_PI * pow(particles[j].radius, 3);
                        radius = pow((3 / (4 * M_PI) * (volume + other_volume)), 1/3);
                        particles[j].accreted = true;

                    }
                    // Collisions - formula based on Physics Stack Exchange answer
                    // (https://physics.stackexchange.com/questions/681396/elastic-collision-3d-eqaution)
                    else {
                        // Normal vector from particle i COM to particle j COM
                        Vector3D n = r.unit();
                        // Reduced mass
                        float m = 1/(1/mass + 1/particles[j].mass);
                        // Impact speed
                        float v_imp = n.dot(velocity - particles[j].velocity);
                        // Velocity change resulting from impulse J = 2mv_imp (coefficient of restitution = 1)
                        velocity -= n * 2*m*v_imp/mass;
                        particles[j].velocity += n * 2*m*v_imp/particles[j].mass;
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
