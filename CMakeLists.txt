cmake_minimum_required(VERSION 3.15)
project(simulation)

# Set the C++ standard to C++17 (or higher if needed)
set(CMAKE_CXX_STANDARD 17)

# Specify the path to vcpkg toolchain file
set(CMAKE_TOOLCHAIN_FILE "C:/Dev/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Set the GLFW package directory if not automatically found by vcpkg
set(glfw3_DIR "C:/Dev/vcpkg/packages/glfw3_x64-windows/share/glfw3/")

# Find OpenGL and required libraries (GLFW, GLM)
find_package(OpenGL REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

# Specify the source files
add_executable(simulation Main.cpp ParticleSimulation.cpp)

# Include the directories for glad
target_include_directories(simulation PRIVATE include)

# Link the libraries to the executable (no need to link GLM since it's header-only)
target_link_libraries(simulation PRIVATE glfw OpenGL::GL)
