# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master"

# Include any dependencies generated for this target.
include examples/CMakeFiles/sample-code-pfunc.dir/depend.make

# Include the progress variables for this target.
include examples/CMakeFiles/sample-code-pfunc.dir/progress.make

# Include the compile flags for this target's objects.
include examples/CMakeFiles/sample-code-pfunc.dir/flags.make

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o: examples/CMakeFiles/sample-code-pfunc.dir/flags.make
examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o: examples/sample-code-pfunc.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o"
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o -c "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples/sample-code-pfunc.cc"

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.i"
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples/sample-code-pfunc.cc" > CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.i

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.s"
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples/sample-code-pfunc.cc" -o CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.s

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.requires:

.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.requires

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.provides: examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.requires
	$(MAKE) -f examples/CMakeFiles/sample-code-pfunc.dir/build.make examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.provides.build
.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.provides

examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.provides.build: examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o


# Object files for target sample-code-pfunc
sample__code__pfunc_OBJECTS = \
"CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o"

# External object files for target sample-code-pfunc
sample__code__pfunc_EXTERNAL_OBJECTS =

examples/sample-code-pfunc: examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o
examples/sample-code-pfunc: examples/CMakeFiles/sample-code-pfunc.dir/build.make
examples/sample-code-pfunc: src/libcmaes.so.0.0.0
examples/sample-code-pfunc: examples/CMakeFiles/sample-code-pfunc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable sample-code-pfunc"
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sample-code-pfunc.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/CMakeFiles/sample-code-pfunc.dir/build: examples/sample-code-pfunc

.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/build

examples/CMakeFiles/sample-code-pfunc.dir/requires: examples/CMakeFiles/sample-code-pfunc.dir/sample-code-pfunc.cc.o.requires

.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/requires

examples/CMakeFiles/sample-code-pfunc.dir/clean:
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" && $(CMAKE_COMMAND) -P CMakeFiles/sample-code-pfunc.dir/cmake_clean.cmake
.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/clean

examples/CMakeFiles/sample-code-pfunc.dir/depend:
	cd "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master" "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master" "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples" "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 10/libcmaes-master/examples/CMakeFiles/sample-code-pfunc.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : examples/CMakeFiles/sample-code-pfunc.dir/depend

