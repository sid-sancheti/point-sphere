# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sancheti/comsci/point-sphere

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sancheti/comsci/point-sphere/build

# Include any dependencies generated for this target.
include CMakeFiles/point-sphere.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/point-sphere.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/point-sphere.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/point-sphere.dir/flags.make

CMakeFiles/point-sphere.dir/src/main.cpp.o: CMakeFiles/point-sphere.dir/flags.make
CMakeFiles/point-sphere.dir/src/main.cpp.o: /home/sancheti/comsci/point-sphere/src/main.cpp
CMakeFiles/point-sphere.dir/src/main.cpp.o: CMakeFiles/point-sphere.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sancheti/comsci/point-sphere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/point-sphere.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/point-sphere.dir/src/main.cpp.o -MF CMakeFiles/point-sphere.dir/src/main.cpp.o.d -o CMakeFiles/point-sphere.dir/src/main.cpp.o -c /home/sancheti/comsci/point-sphere/src/main.cpp

CMakeFiles/point-sphere.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/point-sphere.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sancheti/comsci/point-sphere/src/main.cpp > CMakeFiles/point-sphere.dir/src/main.cpp.i

CMakeFiles/point-sphere.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/point-sphere.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sancheti/comsci/point-sphere/src/main.cpp -o CMakeFiles/point-sphere.dir/src/main.cpp.s

CMakeFiles/point-sphere.dir/include/glad.c.o: CMakeFiles/point-sphere.dir/flags.make
CMakeFiles/point-sphere.dir/include/glad.c.o: /home/sancheti/comsci/point-sphere/include/glad.c
CMakeFiles/point-sphere.dir/include/glad.c.o: CMakeFiles/point-sphere.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/sancheti/comsci/point-sphere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/point-sphere.dir/include/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/point-sphere.dir/include/glad.c.o -MF CMakeFiles/point-sphere.dir/include/glad.c.o.d -o CMakeFiles/point-sphere.dir/include/glad.c.o -c /home/sancheti/comsci/point-sphere/include/glad.c

CMakeFiles/point-sphere.dir/include/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/point-sphere.dir/include/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/sancheti/comsci/point-sphere/include/glad.c > CMakeFiles/point-sphere.dir/include/glad.c.i

CMakeFiles/point-sphere.dir/include/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/point-sphere.dir/include/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/sancheti/comsci/point-sphere/include/glad.c -o CMakeFiles/point-sphere.dir/include/glad.c.s

# Object files for target point-sphere
point__sphere_OBJECTS = \
"CMakeFiles/point-sphere.dir/src/main.cpp.o" \
"CMakeFiles/point-sphere.dir/include/glad.c.o"

# External object files for target point-sphere
point__sphere_EXTERNAL_OBJECTS =

point-sphere: CMakeFiles/point-sphere.dir/src/main.cpp.o
point-sphere: CMakeFiles/point-sphere.dir/include/glad.c.o
point-sphere: CMakeFiles/point-sphere.dir/build.make
point-sphere: /usr/lib/x86_64-linux-gnu/libGLX.so
point-sphere: /usr/lib/x86_64-linux-gnu/libOpenGL.so
point-sphere: CMakeFiles/point-sphere.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/sancheti/comsci/point-sphere/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable point-sphere"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/point-sphere.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/point-sphere.dir/build: point-sphere
.PHONY : CMakeFiles/point-sphere.dir/build

CMakeFiles/point-sphere.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/point-sphere.dir/cmake_clean.cmake
.PHONY : CMakeFiles/point-sphere.dir/clean

CMakeFiles/point-sphere.dir/depend:
	cd /home/sancheti/comsci/point-sphere/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sancheti/comsci/point-sphere /home/sancheti/comsci/point-sphere /home/sancheti/comsci/point-sphere/build /home/sancheti/comsci/point-sphere/build /home/sancheti/comsci/point-sphere/build/CMakeFiles/point-sphere.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/point-sphere.dir/depend

