# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/crystalized/cpp_project/LearnEngine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/crystalized/cpp_project/LearnEngine/build

# Include any dependencies generated for this target.
include Engine/vendor/spdlog/CMakeFiles/spdlog.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.make

# Include the progress variables for this target.
include Engine/vendor/spdlog/CMakeFiles/spdlog.dir/progress.make

# Include the compile flags for this target's objects.
include Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/spdlog.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o -MF CMakeFiles/spdlog.dir/src/spdlog.cpp.o.d -o CMakeFiles/spdlog.dir/src/spdlog.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/spdlog.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/spdlog.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/spdlog.cpp > CMakeFiles/spdlog.dir/src/spdlog.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/spdlog.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/spdlog.cpp -o CMakeFiles/spdlog.dir/src/spdlog.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/stdout_sinks.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o -MF CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o.d -o CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/stdout_sinks.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/stdout_sinks.cpp > CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/stdout_sinks.cpp -o CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/color_sinks.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o -MF CMakeFiles/spdlog.dir/src/color_sinks.cpp.o.d -o CMakeFiles/spdlog.dir/src/color_sinks.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/color_sinks.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/color_sinks.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/color_sinks.cpp > CMakeFiles/spdlog.dir/src/color_sinks.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/color_sinks.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/color_sinks.cpp -o CMakeFiles/spdlog.dir/src/color_sinks.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/file_sinks.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o -MF CMakeFiles/spdlog.dir/src/file_sinks.cpp.o.d -o CMakeFiles/spdlog.dir/src/file_sinks.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/file_sinks.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/file_sinks.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/file_sinks.cpp > CMakeFiles/spdlog.dir/src/file_sinks.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/file_sinks.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/file_sinks.cpp -o CMakeFiles/spdlog.dir/src/file_sinks.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/async.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o -MF CMakeFiles/spdlog.dir/src/async.cpp.o.d -o CMakeFiles/spdlog.dir/src/async.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/async.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/async.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/async.cpp > CMakeFiles/spdlog.dir/src/async.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/async.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/async.cpp -o CMakeFiles/spdlog.dir/src/async.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/cfg.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o -MF CMakeFiles/spdlog.dir/src/cfg.cpp.o.d -o CMakeFiles/spdlog.dir/src/cfg.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/cfg.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/cfg.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/cfg.cpp > CMakeFiles/spdlog.dir/src/cfg.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/cfg.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/cfg.cpp -o CMakeFiles/spdlog.dir/src/cfg.cpp.s

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/flags.make
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o: /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/bundled_fmtlib_format.cpp
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o -MF CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o.d -o CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o -c /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/bundled_fmtlib_format.cpp

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/bundled_fmtlib_format.cpp > CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.i

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog/src/bundled_fmtlib_format.cpp -o CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.s

# Object files for target spdlog
spdlog_OBJECTS = \
"CMakeFiles/spdlog.dir/src/spdlog.cpp.o" \
"CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o" \
"CMakeFiles/spdlog.dir/src/color_sinks.cpp.o" \
"CMakeFiles/spdlog.dir/src/file_sinks.cpp.o" \
"CMakeFiles/spdlog.dir/src/async.cpp.o" \
"CMakeFiles/spdlog.dir/src/cfg.cpp.o" \
"CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o"

# External object files for target spdlog
spdlog_EXTERNAL_OBJECTS =

Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/spdlog.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/stdout_sinks.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/color_sinks.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/file_sinks.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/async.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/cfg.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/src/bundled_fmtlib_format.cpp.o
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/build.make
Engine/vendor/spdlog/libspdlogd.a: Engine/vendor/spdlog/CMakeFiles/spdlog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/crystalized/cpp_project/LearnEngine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX static library libspdlogd.a"
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/spdlog.dir/cmake_clean_target.cmake
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/spdlog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Engine/vendor/spdlog/CMakeFiles/spdlog.dir/build: Engine/vendor/spdlog/libspdlogd.a
.PHONY : Engine/vendor/spdlog/CMakeFiles/spdlog.dir/build

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/clean:
	cd /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/spdlog.dir/cmake_clean.cmake
.PHONY : Engine/vendor/spdlog/CMakeFiles/spdlog.dir/clean

Engine/vendor/spdlog/CMakeFiles/spdlog.dir/depend:
	cd /Users/crystalized/cpp_project/LearnEngine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/crystalized/cpp_project/LearnEngine /Users/crystalized/cpp_project/LearnEngine/Engine/vendor/spdlog /Users/crystalized/cpp_project/LearnEngine/build /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog /Users/crystalized/cpp_project/LearnEngine/build/Engine/vendor/spdlog/CMakeFiles/spdlog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Engine/vendor/spdlog/CMakeFiles/spdlog.dir/depend

