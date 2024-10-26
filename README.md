# Point-Sphere

This program generates a rotating point-sphere (a sphere made of points) entirely in C++.
Dependencies used include GLFW3, Glad, GLM, and GLSL.


## Running the project
1. Git clone the project onto your machine.
```
https://github.com/sid-sancheti/point-sphere.git -d [/your/target/directory]
```
2. Install GLFW onto your machine.

Ubuntu/Debian based systems
```
sudo apt update
sudo apt upgrade -y
sudo apt install libglfw3-dev -y
```
Also, install cmake and make if you haven't already
```
sudo apt install cmake -y
sudo apt install make -y
```

3. Run the project

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
and finally, run the executable.
```
./point-sphere
```
**Voila**, you should see a rotating sphere on your screen.
