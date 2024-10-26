#include <iostream>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

#define NUM_POINTS 2000
#define ESPILON 0.0001
#define SCALE 0.9

#define HEIGHT 405
#define WIDTH 440

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
 * NOT USED
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
    int min = width < height ? width : height;
    int xOffset = (width - min) / 2;
    int yOffset = (height - min) / 2;
    glViewport(xOffset, yOffset, min, min);
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
    int min = WIDTH < HEIGHT ? WIDTH : HEIGHT;
    int xOffset = (WIDTH - min) / 2;
    int yOffset = (HEIGHT - min) / 2;
    glViewport(xOffset, yOffset, min, min);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    populate3Darray();

    /*
     * Enables
     * Note: Enables allow the vertex shader to manipulate certain attributes
     */
    glEnable(GL_PROGRAM_POINT_SIZE);    // Manipulate point size

    std::filesystem::path p = std::filesystem::current_path();
    std::cout << "Relative path:" << p << std::endl;

    std::cout << "Absolute path:" << std::filesystem::absolute(p) << std::endl;
    
    // Set up the shader (relative path is with respect to the build directory)
    Shader shader("/home/sancheti/comsci/point-sphere/src/shaders/vertex.glsl", "/home/sancheti/comsci/point-sphere/src/shaders/fragment.glsl");

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

        // Alter the radians value to increase or decrease the speed of rotation
        glm::mat4 rotation = glm::rotate(
            glm::mat4(1.0f),
            (float)glfwGetTime() * 0.7f,
            glm::vec3(-0.53452f, 0.80178f, 0.26726f)    // A random unit vector (could set this to my mouse position)
        );

        // Passing the rotation matrix to the shader
        shader.use();
        shader.setMat4("rotation", glm::value_ptr(rotation));

        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, NUM_POINTS);

        // Check and call events and swap the buffers
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shader.terminate();
    glfwTerminate();
    return 0;
} /* main() */
