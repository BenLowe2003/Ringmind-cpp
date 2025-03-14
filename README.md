# Ringmind-cpp
2025 codebase for RingMind. The speculative astrophysics project about self organising planetary rings.

#### Authors

- Ben Lowe


## Ringmind Doc:

#### Class:

- Vector3D[3]<float>: Stores the cartesion coordinates of a 3d vector.
  - +<operator>: operator adds two vectors together
  - *<operator>: dot product of two vectors
  - square_norm<func>: gives the norm/magnitude of the vector (Euclidean inner product).
  - norm<func>: gives sqrt of the square_norm function.

- Particle[3]<Vector3D*><float*>: Stores pointers to each particles associated velocity, mass and position.

#### Global Variables:

- velocities[n]<Vector3D>: Array of all the velocities of the particles in the system.
- positions[n]<Vector3D>: Array of all velocities of the particles in the system.
- masses[n]<float>: stores masses of all particles in the system.
- particles[n]<Particle>: stores and array of all particles in the system.


#### Global Functions:

- update_system(float delta_time): Evolves the system over one timestep. IMPORTANT: deallocate memory from either next or current state variabes to avoid memory leak.
  - next_velocities[n]<Vector3D>: Array of all the new velocities of the particles in the system.
  - next_positions[n]<Vector3D>: Array of all new velocities of the particles in the system.
  - next_masses[n]<float>: stores masses of all new particles in the system.
  - delta_momentum[n]<Vector3D>: Stores the total change in momentum over the current timestep.
- evaluate_momentum(int i): Calculates the momentum change for the ith particle.
- integrate(int i): evaluates the new position and velocity for the ith particle.
 
#### CUDA variables
...
