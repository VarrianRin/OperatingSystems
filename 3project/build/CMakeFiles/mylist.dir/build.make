# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/max/Desktop/3project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/max/Desktop/3project/build

# Include any dependencies generated for this target.
include CMakeFiles/mylist.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mylist.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mylist.dir/flags.make

CMakeFiles/mylist.dir/mylist.cpp.o: CMakeFiles/mylist.dir/flags.make
CMakeFiles/mylist.dir/mylist.cpp.o: ../mylist.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/max/Desktop/3project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mylist.dir/mylist.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mylist.dir/mylist.cpp.o -c /home/max/Desktop/3project/mylist.cpp

CMakeFiles/mylist.dir/mylist.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mylist.dir/mylist.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/max/Desktop/3project/mylist.cpp > CMakeFiles/mylist.dir/mylist.cpp.i

CMakeFiles/mylist.dir/mylist.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mylist.dir/mylist.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/max/Desktop/3project/mylist.cpp -o CMakeFiles/mylist.dir/mylist.cpp.s

# Object files for target mylist
mylist_OBJECTS = \
"CMakeFiles/mylist.dir/mylist.cpp.o"

# External object files for target mylist
mylist_EXTERNAL_OBJECTS =

libmylist.a: CMakeFiles/mylist.dir/mylist.cpp.o
libmylist.a: CMakeFiles/mylist.dir/build.make
libmylist.a: CMakeFiles/mylist.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/max/Desktop/3project/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmylist.a"
	$(CMAKE_COMMAND) -P CMakeFiles/mylist.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mylist.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mylist.dir/build: libmylist.a

.PHONY : CMakeFiles/mylist.dir/build

CMakeFiles/mylist.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mylist.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mylist.dir/clean

CMakeFiles/mylist.dir/depend:
	cd /home/max/Desktop/3project/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/max/Desktop/3project /home/max/Desktop/3project /home/max/Desktop/3project/build /home/max/Desktop/3project/build /home/max/Desktop/3project/build/CMakeFiles/mylist.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mylist.dir/depend

