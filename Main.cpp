#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <ctime> 

#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<ProjectionUtils.h>
#include<ShaderUtils.h>

#include"ParticleSimulation.h"


int main(void){


    // Simulation Checks
    int seed = static_cast<unsigned int>(time(0));
    ParticleSimulation sim(5, 1000, seed, 0.1);
    sim.run(100);

	// Initialize GLFW Window
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

	

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

	// Give GLFW hints for OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	// Set the viewport to the size of the window
	glfwSwapInterval(1);

	// Check If GLEW is initialized
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing GLEW." << std::endl;
		return -1;
	}

	// Debugging OpenGL Version
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    float positions[] = {
         0.0f,  0.0f, 0.0f,
         0.5f, -0.5f, -2.0f,
         0.5f,  0.5f, -2.0f,
        -0.5f,  0.5f, 0.0f,
    };

    // Matrix Maths
	float theta_x = 0.0f;
    float theta_y = 0.0f;
    float projMatrix[16];
	ProjectionMatrix(projMatrix, 45.0f, 1.0f, 0.1f, theta_x, theta_y, 2);

	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * 3 * sizeof(float), positions, GL_DYNAMIC_DRAW);

	glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);

	ShaderProgramSource source = ParseShader("Shader.shader");
	std::cout << "Vertex Shader: " << std::endl << source.VertexSource << std::endl;
	std::cout << "Fragment Shader: " << std::endl << source.FragmentSource << std::endl;

    unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

    // Setup colors
	int location = glGetUniformLocation(shader, "u_Color");
	ASSERT(location != -1);
	float r, g, b, a;
	r = 0.2f; g = 0.3f; b = 0.8f; a = 1.0f;
    glUniform4f(location, r, g, b, a);

    // Setup Projection Matrix
    int locationMVP = glGetUniformLocation(shader, "u_MVP");
    ASSERT(locationMVP != -1);
    glUniformMatrix4fv(locationMVP, 1, GL_FALSE, projMatrix);

    //setup view Matrix

    // Bind Buffers to GPU State
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
	


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        // Update color
        r = (r + 0.01f);
        if (r > 1.0f) r = 0.0f;
        glUniform4f(location, r, g, b, a);

		// Update Matrix
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            theta_y += 0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            theta_y -= 0.01f;
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            theta_x += 0.01f;
        }
        else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            theta_x -= 0.01f;
        }
		ProjectionMatrix(projMatrix, 30.0f, 1.0f, 0.1f, theta_x, theta_y, 3);
		glUniformMatrix4fv(locationMVP, 1, GL_FALSE, projMatrix);

        // Update Positions
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 8 * 3 * sizeof(float), positions);

		glBindVertexArray(vao);

		GLCall(glDrawArrays(GL_POINTS, 0, 4));
        glPointSize(10.0f); 

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

	glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}