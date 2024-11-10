#version 330 core

out vec4 FragColor;

// This is where we need to round out the points.

void main(void) {

    // gl_PointCoord gives a normalized [0, 1] range
    vec2 coord = gl_PointCoord - vec2(0.5);
    float distanceFromCenter = length(coord);

    // If the fragment is outside the circle, discard it
    if (distanceFromCenter > 0.5) {
        discard;
    }

    if (gl_FragCoord.z < 0.3) {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0);
    }
}