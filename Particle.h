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

    // Constructor to initialize the particle with position, velocity, and mass
    Particle(const Vector3D& pos = Vector3D(), const Vector3D& vel = Vector3D(), float m = 1.0f)
        : position(pos), velocity(vel), mass(m) {}



    void integrate(float dt) {
        position = position + (velocity * dt); // Update position
        Vector3D acceleration = force * (1.0f / mass); // Calculate acceleration
        velocity = velocity + (acceleration * dt); // Update velocity
        force = Vector3D(0.0f, 0.0f, 0.0f); // Reset force to zero vector
    }

	void interaction(int i, const std::vector<Particle>& particles) {
		for (int j = 0; j < particles.size(); j++) {
			if (i != j) {
				Vector3D r = particles[j].position - position; 
				float square_distance = r.square_norm();
				if (square_distance > 0.0f) {

					force = force + (r * ((-1.0f) * particles[i].mass * particles[j].mass * G / square_distance * std::sqrt(square_distance)));
				}
			}
		}

        // Apply central body force.
		float square_distance = position.square_norm();
		force = force + (position * ((-1.0f) * particles[i].mass * central_body_mass * G / square_distance * std::sqrt(square_distance))); // Apply gravitational force
	}
};

#endif // PARTICLE_H
