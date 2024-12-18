#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 rotation;

void main() {
    gl_Position = rotation * vec4(aPos, 1.0);

    gl_PointSize = (gl_Position.z + 0.5) / 0.23;     // Map z: [-1, 1] to PointSize: [0, ]
}