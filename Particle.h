#ifndef PARTICLE_H
#define PARTICLE_H

#define _USE_MATH_DEFINES
#include <cmath> // For sqrt

const float G = 0.1f; // Gravitational constant 6.6743e-11f
const float central_body_mass = 50 ; // 2.0f * pow(10,12)

const float radius_multiplier = 3; // 122000000.0f;
const float radius_displacement = 0.3; // 92000000.0f
const float scale_factor = 0.2f; // Scale factor for the simulation
const float nu = 0.05f; // Viscosity coefficient for viscous force
const float nu_radius = 0.002f; // characteristic radius for viscous force

#ifndef M_PI
#define M_PI 3.14159265358979323846 // Ensure M_PI is defined (required for GLEW)
#endif

#include <cstdlib>                // For rand() and srand()

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



    Particle() {
        // Random distance and angle for spherical coordinates
        float r = static_cast<float>(rand()) / RAND_MAX * radius_multiplier + radius_displacement; // Random distance jupiters rings
        float theta = (static_cast<float>(rand()) / RAND_MAX) * (2.0f * M_PI); // Random angle in [0, 2*pi)
        float phi = (static_cast<float>(rand()) / RAND_MAX) * M_PI/2; // Random angle in [0, pi)

        // Convert spherical coordinates to Cartesian coordinates
        float x = r * cos(phi) * cos(theta);
        float y = r * cos(phi) * sin(theta);
        float z = r * sin(phi);

        // Create a Vector3D object for the position
		position = Vector3D(x, y, z);
		

        // Find orbital velocity
        float v = sqrt((G * central_body_mass) / r); // Orbital velocity
        float vx = -v * sin(theta);
        float vy = v * cos(theta);
        float vz = 0.0f; // Assuming motion in the xy-plane

        // Create a Vector3D object for the velocity
		velocity = Vector3D(vx, vy, vz);

		mass = 0.1f; // Set mass (currently unused)


    }



    void integrate(float dt) {
        position = position + (velocity * dt); // Update position
        Vector3D acceleration = force * (1.0f / mass); // Calculate acceleration
        velocity = velocity + (acceleration * dt); // Update velocity
        force = Vector3D(0.0f, 0.0f, 0.0f); // Reset force to zero vector
    }

    void interaction(size_t i, std::vector<Particle>& particles, float accretion_probability) {

		// Calculate gravitational force on this particle due to the central body
		force = Vector3D(0.0f, 0.0f, 0.0f); // Reset force to zero vector
		float square_distance = position.square_norm();
		float distance = sqrt(square_distance);
		float force_magnitude = G * mass * (central_body_mass / square_distance); // Gravitational force magnitude
		force -= position.unit() * force_magnitude; // Apply force towards the central body

        // calculate viscous force between particles.
        for (size_t j = 0; j < particles.size(); ++j) {
            float square_distance = (position - particles[j].position).square_norm();
            if (i != j && square_distance < 0.1) {
                Vector3D i_momentum = velocity * mass;
                Vector3D j_momentum = particles[j].velocity * particles[j].mass;
                Vector3D relative_momenutum = i_momentum - j_momentum;
                force -= relative_momenutum * (nu); // Viscous force
            }
        }
    }
};

#endif // PARTICLE_H
};

#endif // PARTICLE_H
