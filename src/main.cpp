#include <iostream>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

#define NUM_POINTS 700
#define ESPILON 0.0001

#define HEIGHT 400
#define WIDTH 640

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";

typedef struct {
    float u, v;
} TwoDPoint;

typedef struct {
    float x, y, z;
} ThreeDPoint;

ThreeDPoint points3D[NUM_POINTS];

/**
 * Populates the 2D array of points using the formula
 * Derived from this paper: https://scholar.rose-hulman.edu/cgi/viewcontent.cgi?article=1387&context=rhumj
 * 
 * @param points2D The 2D array of points to populate
 * @see #populate3Darray()
 */

void populate2Darray(TwoDPoint * points2D) {
    float s = -1 + 1/(NUM_POINTS - 1);
    const float step_size = (2 - 2/(NUM_POINTS - 1))/(NUM_POINTS - 1);
    const float x = 0.12 + 1.1999 * NUM_POINTS;

    for (int i = 0; i < NUM_POINTS; i++, s += step_size) {
        points2D[i].u = s * x;
        points2D[i].v = M_PI/2 + copysignf(1.0f, s) * (1 - sqrt(1 - abs(s)));
    }
} /* populate2Darray() */

/**
 * Calculates the 3D coordinates from the 2D projection of the spiral
 * Uses the {@link #populate2Darray(TwoDPoint *)} function to create the 2D array
 * of points.
 */

void populate3Darray() {
    TwoDPoint * points2D = new TwoDPoint[NUM_POINTS];
    populate2Darray(points2D);
    for (int i = 0; i < NUM_POINTS; i++) {
        float u = points2D[i].u;
        float v = points2D[i].v;

        points3D[i].x = cos(u) * cos(v);
        points3D[i].y = sin(u) * cos(v);
        points3D[i].z = sin(v);
    }

    delete points2D;
    points2D = NULL;
}

/**
 * Callback function: window resize
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
} /* framebuffer_size_callback() */

/**
 * Callback function: Keyboard input
 * Process input from the user
 */
void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

/**
 * Main function
 * Create and manage the window
 */

int main(int, char**) {
    GLFWwindow * window = NULL;
    if (!glfwInit()) {
        std::cerr << "Issue with inializing glfw" << std::endl;
        return -1;
    }

    // Setup OpenGL version (using 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "point-sphere", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        std::cerr << "Failed to create GLFW window" << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Set the viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    populate3Darray();


    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(points3D), points3D, GL_STATIC_DRAW);

    // Set up the vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // Set up the fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link the shaders in a shading program
    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glUseProgram(shaderProgram);

    // Free up unnecessary memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glPointSize(2.0);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, 10);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
} /* main() */
