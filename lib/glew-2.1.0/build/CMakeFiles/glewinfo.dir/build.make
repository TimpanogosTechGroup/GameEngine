# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build

# Include any dependencies generated for this target.
include CMakeFiles/glewinfo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/glewinfo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glewinfo.dir/flags.make

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o: CMakeFiles/glewinfo.dir/flags.make
CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o: /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o   -c /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c > CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.i

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c -o CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.s

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.requires:

.PHONY : CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.requires

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.provides: CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.requires
	$(MAKE) -f CMakeFiles/glewinfo.dir/build.make CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.provides.build
.PHONY : CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.provides

CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.provides.build: CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o


# Object files for target glewinfo
glewinfo_OBJECTS = \
"CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o"

# External object files for target glewinfo
glewinfo_EXTERNAL_OBJECTS =

bin/glewinfo: CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o
bin/glewinfo: CMakeFiles/glewinfo.dir/build.make
bin/glewinfo: lib/libGLEW.so.2.1.0
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libSM.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libICE.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libX11.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libXext.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libGL.so
bin/glewinfo: /usr/lib/x86_64-linux-gnu/libGLU.so
bin/glewinfo: CMakeFiles/glewinfo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/glewinfo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glewinfo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glewinfo.dir/build: bin/glewinfo

.PHONY : CMakeFiles/glewinfo.dir/build

CMakeFiles/glewinfo.dir/requires: CMakeFiles/glewinfo.dir/users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/src/glewinfo.c.o.requires

.PHONY : CMakeFiles/glewinfo.dir/requires

CMakeFiles/glewinfo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glewinfo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glewinfo.dir/clean

CMakeFiles/glewinfo.dir/depend:
	cd /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/cmake /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/cmake /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build /users/guest/b/bbrenk/Documents/GitHub/Repositories/glew-2.1.0/build/CMakeFiles/glewinfo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/glewinfo.dir/depend

