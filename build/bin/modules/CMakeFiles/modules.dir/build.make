# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_SOURCE_DIR = /home/antilopa/Projects/Cpp/LearningCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antilopa/Projects/Cpp/LearningCpp/build

# Include any dependencies generated for this target.
include bin/modules/CMakeFiles/modules.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include bin/modules/CMakeFiles/modules.dir/compiler_depend.make

# Include the progress variables for this target.
include bin/modules/CMakeFiles/modules.dir/progress.make

# Include the compile flags for this target's objects.
include bin/modules/CMakeFiles/modules.dir/flags.make

bin/modules/CMakeFiles/modules.dir/Vector.cpp.o: bin/modules/CMakeFiles/modules.dir/flags.make
bin/modules/CMakeFiles/modules.dir/Vector.cpp.o: /home/antilopa/Projects/Cpp/LearningCpp/src/modules/Vector.cpp
bin/modules/CMakeFiles/modules.dir/Vector.cpp.o: bin/modules/CMakeFiles/modules.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/antilopa/Projects/Cpp/LearningCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bin/modules/CMakeFiles/modules.dir/Vector.cpp.o"
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT bin/modules/CMakeFiles/modules.dir/Vector.cpp.o -MF CMakeFiles/modules.dir/Vector.cpp.o.d -o CMakeFiles/modules.dir/Vector.cpp.o -c /home/antilopa/Projects/Cpp/LearningCpp/src/modules/Vector.cpp

bin/modules/CMakeFiles/modules.dir/Vector.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/modules.dir/Vector.cpp.i"
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/antilopa/Projects/Cpp/LearningCpp/src/modules/Vector.cpp > CMakeFiles/modules.dir/Vector.cpp.i

bin/modules/CMakeFiles/modules.dir/Vector.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/modules.dir/Vector.cpp.s"
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/antilopa/Projects/Cpp/LearningCpp/src/modules/Vector.cpp -o CMakeFiles/modules.dir/Vector.cpp.s

# Object files for target modules
modules_OBJECTS = \
"CMakeFiles/modules.dir/Vector.cpp.o"

# External object files for target modules
modules_EXTERNAL_OBJECTS =

bin/modules/libmodules.a: bin/modules/CMakeFiles/modules.dir/Vector.cpp.o
bin/modules/libmodules.a: bin/modules/CMakeFiles/modules.dir/build.make
bin/modules/libmodules.a: bin/modules/CMakeFiles/modules.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/antilopa/Projects/Cpp/LearningCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmodules.a"
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && $(CMAKE_COMMAND) -P CMakeFiles/modules.dir/cmake_clean_target.cmake
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/modules.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bin/modules/CMakeFiles/modules.dir/build: bin/modules/libmodules.a
.PHONY : bin/modules/CMakeFiles/modules.dir/build

bin/modules/CMakeFiles/modules.dir/clean:
	cd /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules && $(CMAKE_COMMAND) -P CMakeFiles/modules.dir/cmake_clean.cmake
.PHONY : bin/modules/CMakeFiles/modules.dir/clean

bin/modules/CMakeFiles/modules.dir/depend:
	cd /home/antilopa/Projects/Cpp/LearningCpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/antilopa/Projects/Cpp/LearningCpp /home/antilopa/Projects/Cpp/LearningCpp/src/modules /home/antilopa/Projects/Cpp/LearningCpp/build /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules /home/antilopa/Projects/Cpp/LearningCpp/build/bin/modules/CMakeFiles/modules.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : bin/modules/CMakeFiles/modules.dir/depend

