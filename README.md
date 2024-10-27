# Point-Sphere

This program generates a rotating point-sphere (a sphere made of points) entirely in C++.
Dependencies used include GLFW3, Glad, GLM, and GLSL.

![sphere-resize](https://github.com/user-attachments/assets/cc538959-b377-4833-b8c6-d0404b5d0fa8)

## Running the project

## 1. Git clone the project onto your machine.
```
https://github.com/sid-sancheti/point-sphere.git -d [/your/target/directory]
```
## 2. Setting up the environment

### Ubuntu/Debian based systems
I'm not to familiar with other operating systems, but there are online resources available that can guide you through the
installation process for the dependencies we need.

Install GLFW, an open-source API for displaying OpenGL code on your screen.
```
sudo apt update
sudo apt upgrade -y
sudo apt install libglfw3-dev
```
Also, install cmake and make if you haven't already
```
sudo apt install cmake -y
sudo apt install make -y
```

## 3. Run the project

Navigate to the project directory
```
cd /path/to/project/directory
mkdir build
cd build
```

and run cmake to generate the Makefile.
```
cmake ..
```
Run the makefile
```
make
```
and finally, run the executable **from the parent directory**. It won't work otherwise because relative file path starts
from where the project is ran. We need the relative file path to start at the parent directory because we need to access
the shader files in the src directory.
```
cd ..
./build/point-sphere
```
**Voila**, you should see a rotating sphere on your screen.
