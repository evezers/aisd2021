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
CMAKE_COMMAND = /home/evezers/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/evezers/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/203.7148.70/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/evezers/CLionProjects/lab2_16

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/evezers/CLionProjects/lab2_16/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/lab2_cycle.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab2_cycle.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab2_cycle.dir/flags.make

CMakeFiles/lab2_cycle.dir/main.c.o: CMakeFiles/lab2_cycle.dir/flags.make
CMakeFiles/lab2_cycle.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/lab2_cycle.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab2_cycle.dir/main.c.o   -c /home/evezers/CLionProjects/lab2_16/main.c

CMakeFiles/lab2_cycle.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_cycle.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evezers/CLionProjects/lab2_16/main.c > CMakeFiles/lab2_cycle.dir/main.c.i

CMakeFiles/lab2_cycle.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_cycle.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evezers/CLionProjects/lab2_16/main.c -o CMakeFiles/lab2_cycle.dir/main.c.s

CMakeFiles/lab2_cycle.dir/queue_vector.c.o: CMakeFiles/lab2_cycle.dir/flags.make
CMakeFiles/lab2_cycle.dir/queue_vector.c.o: ../queue_vector.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/lab2_cycle.dir/queue_vector.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab2_cycle.dir/queue_vector.c.o   -c /home/evezers/CLionProjects/lab2_16/queue_vector.c

CMakeFiles/lab2_cycle.dir/queue_vector.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_cycle.dir/queue_vector.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evezers/CLionProjects/lab2_16/queue_vector.c > CMakeFiles/lab2_cycle.dir/queue_vector.c.i

CMakeFiles/lab2_cycle.dir/queue_vector.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_cycle.dir/queue_vector.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evezers/CLionProjects/lab2_16/queue_vector.c -o CMakeFiles/lab2_cycle.dir/queue_vector.c.s

CMakeFiles/lab2_cycle.dir/queue_cycle.c.o: CMakeFiles/lab2_cycle.dir/flags.make
CMakeFiles/lab2_cycle.dir/queue_cycle.c.o: ../queue_cycle.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/lab2_cycle.dir/queue_cycle.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab2_cycle.dir/queue_cycle.c.o   -c /home/evezers/CLionProjects/lab2_16/queue_cycle.c

CMakeFiles/lab2_cycle.dir/queue_cycle.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_cycle.dir/queue_cycle.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evezers/CLionProjects/lab2_16/queue_cycle.c > CMakeFiles/lab2_cycle.dir/queue_cycle.c.i

CMakeFiles/lab2_cycle.dir/queue_cycle.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_cycle.dir/queue_cycle.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evezers/CLionProjects/lab2_16/queue_cycle.c -o CMakeFiles/lab2_cycle.dir/queue_cycle.c.s

CMakeFiles/lab2_cycle.dir/calculate.c.o: CMakeFiles/lab2_cycle.dir/flags.make
CMakeFiles/lab2_cycle.dir/calculate.c.o: ../calculate.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/lab2_cycle.dir/calculate.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab2_cycle.dir/calculate.c.o   -c /home/evezers/CLionProjects/lab2_16/calculate.c

CMakeFiles/lab2_cycle.dir/calculate.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_cycle.dir/calculate.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evezers/CLionProjects/lab2_16/calculate.c > CMakeFiles/lab2_cycle.dir/calculate.c.i

CMakeFiles/lab2_cycle.dir/calculate.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_cycle.dir/calculate.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evezers/CLionProjects/lab2_16/calculate.c -o CMakeFiles/lab2_cycle.dir/calculate.c.s

CMakeFiles/lab2_cycle.dir/io.c.o: CMakeFiles/lab2_cycle.dir/flags.make
CMakeFiles/lab2_cycle.dir/io.c.o: ../io.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/lab2_cycle.dir/io.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/lab2_cycle.dir/io.c.o   -c /home/evezers/CLionProjects/lab2_16/io.c

CMakeFiles/lab2_cycle.dir/io.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab2_cycle.dir/io.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/evezers/CLionProjects/lab2_16/io.c > CMakeFiles/lab2_cycle.dir/io.c.i

CMakeFiles/lab2_cycle.dir/io.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab2_cycle.dir/io.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/evezers/CLionProjects/lab2_16/io.c -o CMakeFiles/lab2_cycle.dir/io.c.s

# Object files for target lab2_cycle
lab2_cycle_OBJECTS = \
"CMakeFiles/lab2_cycle.dir/main.c.o" \
"CMakeFiles/lab2_cycle.dir/queue_vector.c.o" \
"CMakeFiles/lab2_cycle.dir/queue_cycle.c.o" \
"CMakeFiles/lab2_cycle.dir/calculate.c.o" \
"CMakeFiles/lab2_cycle.dir/io.c.o"

# External object files for target lab2_cycle
lab2_cycle_EXTERNAL_OBJECTS =

lab2_cycle: CMakeFiles/lab2_cycle.dir/main.c.o
lab2_cycle: CMakeFiles/lab2_cycle.dir/queue_vector.c.o
lab2_cycle: CMakeFiles/lab2_cycle.dir/queue_cycle.c.o
lab2_cycle: CMakeFiles/lab2_cycle.dir/calculate.c.o
lab2_cycle: CMakeFiles/lab2_cycle.dir/io.c.o
lab2_cycle: CMakeFiles/lab2_cycle.dir/build.make
lab2_cycle: CMakeFiles/lab2_cycle.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable lab2_cycle"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab2_cycle.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab2_cycle.dir/build: lab2_cycle

.PHONY : CMakeFiles/lab2_cycle.dir/build

CMakeFiles/lab2_cycle.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab2_cycle.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab2_cycle.dir/clean

CMakeFiles/lab2_cycle.dir/depend:
	cd /home/evezers/CLionProjects/lab2_16/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/evezers/CLionProjects/lab2_16 /home/evezers/CLionProjects/lab2_16 /home/evezers/CLionProjects/lab2_16/cmake-build-debug /home/evezers/CLionProjects/lab2_16/cmake-build-debug /home/evezers/CLionProjects/lab2_16/cmake-build-debug/CMakeFiles/lab2_cycle.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab2_cycle.dir/depend
