# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /snap/clion/235/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/235/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/max/Desktop/2project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/Desktop/2project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/2project.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/2project.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/2project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/2project.dir/flags.make

CMakeFiles/2project.dir/main.cpp.o: CMakeFiles/2project.dir/flags.make
CMakeFiles/2project.dir/main.cpp.o: /home/max/Desktop/2project/main.cpp
CMakeFiles/2project.dir/main.cpp.o: CMakeFiles/2project.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/Desktop/2project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/2project.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/2project.dir/main.cpp.o -MF CMakeFiles/2project.dir/main.cpp.o.d -o CMakeFiles/2project.dir/main.cpp.o -c /home/max/Desktop/2project/main.cpp

CMakeFiles/2project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/2project.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/max/Desktop/2project/main.cpp > CMakeFiles/2project.dir/main.cpp.i

CMakeFiles/2project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/2project.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/max/Desktop/2project/main.cpp -o CMakeFiles/2project.dir/main.cpp.s

# Object files for target 2project
2project_OBJECTS = \
"CMakeFiles/2project.dir/main.cpp.o"

# External object files for target 2project
2project_EXTERNAL_OBJECTS =

2project: CMakeFiles/2project.dir/main.cpp.o
2project: CMakeFiles/2project.dir/build.make
2project: lib2project_lib.a
2project: CMakeFiles/2project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/Desktop/2project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 2project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/2project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/2project.dir/build: 2project
.PHONY : CMakeFiles/2project.dir/build

CMakeFiles/2project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/2project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/2project.dir/clean

CMakeFiles/2project.dir/depend:
	cd /home/max/Desktop/2project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/Desktop/2project /home/max/Desktop/2project /home/max/Desktop/2project/cmake-build-debug /home/max/Desktop/2project/cmake-build-debug /home/max/Desktop/2project/cmake-build-debug/CMakeFiles/2project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/2project.dir/depend
