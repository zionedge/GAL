# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /homes/eva/xp/xpagac06/GAL/OGDF

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /homes/eva/xp/xpagac06/GAL/OGDF

# Include any dependencies generated for this target.
include CMakeFiles/ex-check-build-mode.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex-check-build-mode.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex-check-build-mode.dir/flags.make

CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o: CMakeFiles/ex-check-build-mode.dir/flags.make
CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o: doc/examples/special/check-build-mode.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/homes/eva/xp/xpagac06/GAL/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o"
	/usr/local/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o -c /homes/eva/xp/xpagac06/GAL/OGDF/doc/examples/special/check-build-mode.cpp

CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.i"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /homes/eva/xp/xpagac06/GAL/OGDF/doc/examples/special/check-build-mode.cpp > CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.i

CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.s"
	/usr/local/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /homes/eva/xp/xpagac06/GAL/OGDF/doc/examples/special/check-build-mode.cpp -o CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.s

# Object files for target ex-check-build-mode
ex__check__build__mode_OBJECTS = \
"CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o"

# External object files for target ex-check-build-mode
ex__check__build__mode_EXTERNAL_OBJECTS =

doc/examples/special/ex-check-build-mode: CMakeFiles/ex-check-build-mode.dir/doc/examples/special/check-build-mode.cpp.o
doc/examples/special/ex-check-build-mode: CMakeFiles/ex-check-build-mode.dir/build.make
doc/examples/special/ex-check-build-mode: libOGDF.a
doc/examples/special/ex-check-build-mode: libCOIN.a
doc/examples/special/ex-check-build-mode: CMakeFiles/ex-check-build-mode.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/homes/eva/xp/xpagac06/GAL/OGDF/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable doc/examples/special/ex-check-build-mode"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex-check-build-mode.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex-check-build-mode.dir/build: doc/examples/special/ex-check-build-mode

.PHONY : CMakeFiles/ex-check-build-mode.dir/build

CMakeFiles/ex-check-build-mode.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex-check-build-mode.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex-check-build-mode.dir/clean

CMakeFiles/ex-check-build-mode.dir/depend:
	cd /homes/eva/xp/xpagac06/GAL/OGDF && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /homes/eva/xp/xpagac06/GAL/OGDF /homes/eva/xp/xpagac06/GAL/OGDF /homes/eva/xp/xpagac06/GAL/OGDF /homes/eva/xp/xpagac06/GAL/OGDF /homes/eva/xp/xpagac06/GAL/OGDF/CMakeFiles/ex-check-build-mode.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex-check-build-mode.dir/depend

