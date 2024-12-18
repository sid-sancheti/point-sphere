#include <iostream>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include <glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>      // For print vectors and matrices

#include <random>
#include <shader.h>

#include <filesystem>
namespace fs = std::filesystem;

#define NUM_POINTS 2000
#define ESPILON 0.0001
#define SCALE 0.9

#define HEIGHT 405
#define WIDTH 440

// Set to 1 to enable mouse tracking
#define MOUSE_TRACKING 0

// w is only used for debugging purposes; it is always 1.0
typedef struct {
    float x, y;
} vec2local;

typedef struct {
    float x, y, z;
} vec3local;

vec3local points3D[NUM_POINTS];

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
} /* populate3Darray() */

void populate3Drand() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(-180.0, 180.0);


    float dist = 200.0;
    for (int i = 0; i < NUM_POINTS; i++) {
        double theta = dis(gen);
        double phi = dis(gen);

        points3D[i].x = SCALE * sin(theta) * cos(phi);
        points3D[i].y = SCALE * sin(theta) * sin(phi);
        points3D[i].z = SCALE * cos(theta);
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
void process_input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
} /* processInput() */

/**
 * Main function
 * Create and manage the window
 */

int main(int argc, char* argv[]) {
    // Seed the random number generator
    srand(1);

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

    // Set the viewport to the middle of the window
    int min = WIDTH < HEIGHT ? WIDTH : HEIGHT;
    int xOffset = (WIDTH - min) / 2;
    int yOffset = (HEIGHT - min) / 2;
    glViewport(xOffset, yOffset, min, min);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    populate3Darray();
    // populate3Drand();

    /*
     * Allows the vertex shader to manipulate the point size
     */
    glEnable(GL_PROGRAM_POINT_SIZE);    // Manipulate point size

    if (argc == 0 || argv[0] == nullptr) {
        std::cerr << "Unable to determine the executable path." << std::endl;
        return 1;
    }

    // Get the executable's directory
    fs::path execPath = fs::absolute(argv[0]);
    fs::path execDir = execPath.parent_path();

    // Construct shader paths relative to the executable directory
    fs::path vertexShaderPath = execDir / "../src/shaders/vertex.glsl";
    fs::path fragmentShaderPath = execDir / "../src/shaders/fragment.glsl";
    // Set up the shader
    Shader shader(vertexShaderPath.string(), fragmentShaderPath.string());

    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);

    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Pass data to VBO
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(float) * NUM_POINTS, points3D, GL_STATIC_DRAW);

    // Tell the VAO how to interpret the data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(VAO);

    // Default value of the direction vector
    glm::vec3 directionVector = glm::normalize(glm::vec3(-2, 3, 1));
    
    // Main loop
    while (!glfwWindowShouldClose(window)) {
        // Process input
        process_input(window);

        #if MOUSE_TRACKING

        // Get mouse position and window position to make the sphere rotate in the direction
        // of the user's mouse
        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        double relX = -1.0f * (float) width / 2.0f + mouseX;
        double relY = (float) height / 2.0f - mouseY;

        directionVector = glm::normalize(glm::vec3(relX, relY, 5.0f));
        #endif

        // std::cout << "Direction vector: " << glm::to_string(directionVector) << std::endl;

        // Render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Alter the radians value to increase or decrease the speed of rotation
        glm::mat4 rotation = glm::rotate(
            glm::mat4(1.0f),
            (float)glfwGetTime() * 0.07f,
            glm::normalize(directionVector)    // A random unit vector (could set this to my mouse position)
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
