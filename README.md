# Ringmind-cpp
2025 codebase for Ringmind, the speculative astrophysics project about self organising planetary rings. This is a interdisciplinary arts-humanities-science project led by [Bronislaw Szerszynski](https://www.lancaster.ac.uk/sociology/people/bronislaw-szerszynski). The project is currently being rewritten in C++.

#### Authors

- [Ben Lowe](https://github.com/BenLowe2003)
- [Charles Proudfoot](https://github.com/Kitarlie)
- [Tushaar Davies](https://github.com/TJRavenD)

## Ringmind Doc:

#### Class:

- Vector3D[3]<float>: Stores the Cartesian coordinates of a 3D vector.
  - +<operator>: operator adds two vectors together (includes corresponding += <operator>)
  - -<operator>: operator subtracts one vector from another (includes corresponding -= <operator>)
  - *<operator>: multiplies a vector by a scalar
  - /<operator>: divides a vector by a scalar
  - dot<func>: returns the dot product of two vectors
  - square_norm<func>: returns the norm/magnitude of the vector (Euclidean inner product)
  - norm<func>: returns sqrt of the square_norm function
  - unit<func>: returns the unit vector in the direction of the vector

- Particle[4]<Vector3D*><float*>: Stores pointers to each particle's position, velocity, acceleration and mass.
  - Position<Vector3D*>: the position of the particle with respect to the initial position of the central mass
  - Velocity<Vector3D*>: the instantaneous velocity of the particle
  - Force<Vector3D*>: the instantaneous force acting on the particle
  - integrate<func>: updates the velocity and position of the particle (Euler-Cromer method)

#### Global Variables:

- particles[n]<Particle>: stores and array of all particles in the system.

#### Global Functions:

- run: evolves the system over a given number of steps.
 
#### CUDA variables
...
