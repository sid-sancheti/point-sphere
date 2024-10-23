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

TwoDPoint points[NUM_POINTS];

int main(int, char**) {
    GLFWwindow * window = NULL;
    if (!glfwInit()) {
        cerr << "Issue with inializing glfw" << endl;
        return -1;
    }

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

    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    window = NULL;
    return 0;
}

/**
 * Populates the 2D array of points using the formula
 * Derived from this paper: https://scholar.rose-hulman.edu/cgi/viewcontent.cgi?article=1387&context=rhumj
 */

void populate2Darray() {
    float s = -1 + 1/(NUM_POINTS - 1);
    const float step_size = (2 - 2/(NUM_POINTS - 1))/(NUM_POINTS - 1);
    const float x = 0.12 + 1.1999 * NUM_POINTS;


    for (int i = 0; i < NUM_POINTS; i++, s += step_size) {
        points[i].u = s * x;
        points[i].v = M_PI/2 + copysignf(1.0f, s) * (1 - sqrt(1 - abs(s)));
    }

    
}