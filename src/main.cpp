#include <iostream>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#define NUM_POINTS 2000
#define ESPILON 0.0001
#define SCALE 0.9

#define HEIGHT 405
#define WIDTH 440

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

// w is only used for debugging purposes; it is always 1.0
typedef struct {
    float x, y;
} vec2local;

typedef struct {
    float x, y, z;
} vec3local;

vec3local points3D[3 * NUM_POINTS];

/**
 * Generates a spiral of points in 3D space
 * 
 * @param points2D The 2D array of points to populate; z is always 0
 * @param numPoints The number of points to generate
 */
void generateSpiral(vec3local * points2D, int numPoints) {
    float s = -1.0f;
    const float step_size = 2.0f /(numPoints - 1);
    for (int i = 0; i < numPoints; i++, s += step_size) {
        points2D[i].x = s;
        points2D[i].y = M_PI/2 * copysignf(1.0f, s) * (1 - sqrt(1 - abs(s)));
        points2D[i].z = 0.0f;
    }
}
/**
 * Populates the 2D array of points using the formula
 * Derived from this paper: https://scholar.rose-hulman.edu/cgi/viewcontent.cgi?article=1387&context=rhumj
 * 
 * @param points2D The 2D array of points to populate
 * @see #populate3Darray()
 */

void populate2Darray(vec2local * points2D) {
    float s = -1 + 1.0f /(NUM_POINTS - 1);
    const float step_size = (2.0f - 2.0f/(NUM_POINTS - 1))/(NUM_POINTS - 1);
    const float x = 0.1 + 1.2 * NUM_POINTS;

    for (int i = 0; i < NUM_POINTS; i++, s += step_size) {
        points2D[i].x = s * x;
        points2D[i].y = M_PI/2 * copysignf(1.0f, s) * (1 - sqrt(1 - abs(s)));
    }
} /* populate2Darray() */

/**
 * Calculates the 3D coordinates from the 2D projection of the spiral
 * Uses the {@link #populate2Darray(TwoDPoint *)} function to create the 2D array
 * of points.
 */

void populate3Darray() {
    vec2local points2D[NUM_POINTS];
    populate2Darray(points2D);
    for (int i = 0; i < NUM_POINTS; i++) {
        float u = points2D[i].x;
        float v = points2D[i].y;

        points3D[i].x = SCALE * cos(u) * cos(v);
        points3D[i].y = SCALE * sin(u) * cos(v);
        points3D[i].z = SCALE * sin(v);
    }
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

    // TwoDPoint points2D[NUM_POINTS];
    // populate2Darray(points2D);
    // for (int i = 0; i < NUM_POINTS; i++) {
    //     points2D[i].u /= 840.0f;
    // }
    vec3local spiralPoints[NUM_POINTS];
    generateSpiral(spiralPoints, NUM_POINTS);
    
    populate3Darray();

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

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * NUM_POINTS, points3D, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    glPointSize(2.0f);
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        processInput(window);

        // Render
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, NUM_POINTS);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
} /* main() */
