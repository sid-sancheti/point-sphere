# Point-Sphere

This program generates a rotating point-sphere (a sphere made of points) entirely in C++.
Dependencies used include GLFW3, Glad, GLM, and GLSL.

![sphere-resize](https://github.com/user-attachments/assets/cc538959-b377-4833-b8c6-d0404b5d0fa8)

## Running the project

## 1. Git clone the project onto your machine.

```{Bash}
https://github.com/sid-sancheti/point-sphere.git -d [/your/target/directory]
```

## 2. Setting up the environment

### Ubuntu/Debian based systems

I'm not to familiar with other operating systems, but there are online resources available that can guide you through the
installation process for the dependencies we need.

Install GLFW, an open-source API for displaying OpenGL code on your screen.

```{Bash}
sudo apt update
sudo apt upgrade -y
sudo apt install libglfw3-dev
```

Also, install cmake and make if you haven't already

```{Bash}
sudo apt install cmake -y
sudo apt install make -y
```

## 3. Run the project

Navigate to the project directory

```{Bash}
cd /path/to/project/directory
mkdir build
cd build
```

and run cmake to generate the Makefile.

```{Bash}
cmake ..
```

Run the makefile

``` {Bash}
make
```

and finally, run the executable

```{Bash}
./point-sphere
```

**Voilà**, you should see a rotating sphere on your screen.
