#include <iostream>
#include <math.h>

#define GLFW_INCLUDE_NONE
#include "glad.h"
#include <GLFW/glfw3.h>

#define NUM_POINTS 700
#define ESPILON 0.0001

using namespace std;

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
 */

TwoDPoint * populate2Darray() {
    TwoDPoint * points2D = new TwoDPoint[NUM_POINTS];
    float s = -1 + 1/(NUM_POINTS - 1);
    const float step_size = (2 - 2/(NUM_POINTS - 1))/(NUM_POINTS - 1);
    const float x = 0.12 + 1.1999 * NUM_POINTS;

    for (int i = 0; i < NUM_POINTS; i++, s += step_size) {
        points2D[i].u = s * x;
        points2D[i].v = M_PI/2 + copysignf(1.0f, s) * (1 - sqrt(1 - abs(s)));
    }

    return points2D;
}

void populate3Darray() {
    TwoDPoint * points2D = populate2Darray();
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

int main(int, char**) {
    GLFWwindow * window = NULL;
    if (!glfwInit()) {
        cerr << "Issue with inializing glfw" << endl;
        return -1;
    }

    // Setup OpenGL version (using 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    populate3Darray();

    window = glfwCreateWindow(640, 400, "point-sphere", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        cerr << "Could not create window" << endl;
        window = NULL;
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Could not load OpenGL" << endl;
        glfwTerminate();
        window = NULL;
        return -1;
    }

    // glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    window = NULL;
    return 0;
}