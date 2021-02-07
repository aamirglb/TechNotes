# CMake
## From CMake Cookbook

[Source Code](https://github.com/dev-cafe/cmake-cookbook)

CMake and its siblings, CTest, CPack, and CDash, have emerged as the leading toolset for building software from sources

CMake goal: provide a set of tools that would make it easier to configure, build, test, and
deploy the same project across different platforms.
[CMake Story](https://www.aosabook.org/en/cmake.html)

CMake is a build-system generator, offering a powerful domain-specific language (DSL) to describe what the build system should achieve. CMake, allows the generation of *platform-native build systems* with the same set of CMake scripts.

#### CMake software toolset
**CMake** lets you describe how your project, whether building an
executable, libraries, or both, has to be configured, built, and installed on all major hardware and operating systems.
**CTest** allows you to define tests, test suites, and set how they should be executed.
**CPack** offers a DSL for all your packaging needs, whether your project should be bundled and distributed in source code or platform-native binary form.
**CDash** will be useful for reporting the results of tests for your project to an online dashboard.

```bash
git clone --single-branch -b v1.0 https://github.com/dev-cafe/cmake-cookbook.git
```

```bash
$ cmake_version="3.5.2"
$ target_path=$HOME/Deps/cmake/${cmake_version}
$ cmake_url="https://cmake.org/files/v${cmake_version%.*}/cmake-${cmake_version}-Linux-x86_64.tar.g
$ mkdir -p "${target_path}"
$ curl -Ls "${cmake_url}" | tar -xz -C "${target_path}" --strip-components=1
$ export PATH=$HOME/Deps/cmake/${cmake_version}/bin${PATH:+:$PATH}
$ cmake --version
```

The Ninja program is a different build-automation tool that works on
GNU/Linux, macOS, and Windows. Ninja is a new build tool, with a focus on
speed, especially for incremental rebuilds.

```bash
$ virtualenv --python=python3.5 venv
$ source venv/bin/activate
$ pip install -r requirements.txt
```

```bash
$ sudo apt-get install libatlas-dev liblapack-dev liblapacke-dev
```

**Eigen** linear algebra template library
```bash
$ eigen_version="3.3.4"
$ mkdir -p eigen
$ curl -Ls http://bitbucket.org/eigen/eigen/get/${eigen_version}.tar.gz | tar -xz -C eigen --strip-
$ cd eigen
cm$ ake -H. -Bbuild_eigen -DCMAKE_INSTALL_PREFIX="$HOME/Deps/eigen" &> /dev/null
$ cmake --build build_eigen -- install &> /dev/null
```
#### Cross-compilers
```bash
$ sudo apt-get install gcc-mingw-w64 g++-mingw-w64 gfortran-mingw-w64
```

CMake is a build system generator particularly suited to being platform- and compiler-independent.

[CMake language comprehensive documentation](https://cmake.org/cmake/help/latest/)

The name of the file is case sensitive; it has to be called **CMakeLists.txt** for CMake to be able to parse it.

```cmake
# Minimum required version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
# Project name and suppported language
project(recipe-01 LANGUAGES CXX)
# Create a new target
add_executable(hello-world hello-world.cpp)
```

```bash
$ mkdir -p build
$ cd build
$ cmake ..         # generate build files
$ cmake --build .  # compile source code and generate executable
```

The CMake language is case insensitive, but the arguments are case sensitive.

In CMake, C++ is the default programming language. However, we suggest to always explicitly state the project’s language in the *project* command using the *LANGUAGES* option.

```bash
cmake -H. -Bbuild
# -H: Search for the root CMakeLists.txt in given directory (in above case current directory)
# -B: Generate all files i directory build
```

```bash
cmake . # in-source build (undesirable)
```

```bash
$ cmake --build .
# This command is a generic, cross-platform wrapper to the native build command for the chosen generator.
$ cmake --build . --target help
# Show a list of available targets in Makefile
```
CMake generates the corresponding instructions for the chosen build system. By default, on GNU/Linux and macOS systems, CMake employs the *Unix Makefiles* generator. On Windows, *Visual Studio* is the default generator.

CMake generate following files:
**CMakeFiles** : Directory which contains temporary files, used by CMake for detecting the operating system, compiler, and so on. In addition, depending on the chosen generator, it also contains project-specific files.
**cmake_install.cmake** : A CMake script handling install rules, which is used at install time.
**CMakeCache.txt** : The CMake cache, as the filename suggests. This file is used by CMake when re-running the configuration.

```bash
$ cmake -G Ninja ..
$ cmake --build .
```

```cmake
# Create new target (static library)
add_library(message STATIC Message.hpp Message.cpp)
add_executable(hello hello.cpp)
target_link_libraries(hello message)
```

`add_library()`: generate build tool instructions for compiling specified source into library. Second argument can be `STATIC`,  `SHARED`, `OBJECT`, `MODULE`, `IMPORTED`, `INTERFACE`, `ALIAS`.

`target_link_libraries()`: Link library into executable.

[Blog post by Craig Scott](https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/)

**generator expression syntax**: `$<TARGET_OBJECTS:message-objs>`. Generator expressions are constructs that CMake evaluates at generation time, right after configuration time, to produce
configuration-specific build output.

```cmake
add_library(message-objs
    OBJECT 
    Message.hpp
    Message.cpp
)

add_library(message-shared
    SHARED
    $<TARGET_OBJECTS:message-objs>
)
set_target_properties(message-shared
    PROPERTIES
    OUTPUT_NAME "message"
)
add_library(message-static
    STATIC
    $<TARGET_OBJECTS:message-objs>
)
set_target_properties(message-static
    PROPERTIES
    OUTPUT_NAME "message"
)

```

dynamic shared object (DSO)

The CMake language is fairly large and consists of basic control constructs, CMake-specific commands, and infrastructure for modularly extending the language with new functions. [CMake Language Reference](https://cmake.org/cmake/help/latest/manual/cmake-language.7.html) 

### CMake conditionals
```cmake
if()
else()
endif()
```

`objdump -x` command on GNU/Linux to verify an executable

`BUILD_SHARED_LIBS` is a global flag offered by CMake.

`if(USE_LIBRARY) ... else(USE_LIBRARY) ... endif(USE_LIBRARY)`

The recommended way to toggle behavior in the build
system generation for your project is to present logical switches as options in your CMakeLists.txt using the option() command.

Pass the information to CMake via its -D CLI option
`cmake -D USE_LIBRARY=ON ... `. The -D switch is used to set any type of variable for CMake: logicals, paths,
and so forth.

```option(<option_variable> "help string" [initial value])```

CMake offers the `cmake_dependent_option()` command to define options that depend on other options

CMake has mechanisms in place to extend its syntax and capabilities through the inclusion of modules, either shipped with CMake itself or custom ones.
`include(CMakeDependentOption)`

CMake is sophisticated enough to select the most appropriate
compiler given the platform and the generator. CMake is also able to set compiler flags to a sane set of defaults.

### Selecting compiler
CMake stores compilers for each language in the `CMAKE_<LANG>_COMPILER` variable, where `<LANG>` is any of the
supported languages, for our purposes CXX , C , or Fortran . The user can set this variable in one of two ways:
```bash
$ cmake -D CMAKE_CXX_COMPILER=clang++ ..
$ env CXX=clang++ cmake ..
```

CMake offers the --system-information flag, which will dump all information about your system to the screen or a file.
```bash
$ cmake --system-information information.txt
```

#### Additional variables
```cmake
CMAKE_<LANG>_COMPILER_LOADED: If language is enabled
CMAKE_<LANG>_COMPILER_ID: 
CMAKE_COMPILER_IS_GNU<LANG>:
CMAKE_<LANG>_COMPILER_VERSION: major[.minor[.patch[.tweak]]] format
```

CMake has the notion of build types or configurations, such as Debug, Release, and so forth. The variable governing the configuration to be used when generating the build system is `CMAKE_BUILD_TYPE`. This variable is empty by default, and the values recognized by CMake are: `Debug`, `Release`, `RelWithDebInfo`, `MinSizeRel`.

```cmake
message(STATUS "C++ flags, Debug configuration: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "C++ flags, Release configuration: ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "C++ flags, RelWithDebInfo configuration: ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
message(STATUS "C++ flags, Minimal Release configuration: ${CMAKE_CXX_FLAGS_MINSIZEREL}")
```

```bash
cmake -D CMAKE_BUID_TYPE=Debug ..
```

For *single-configuration* generators, such as Unix Makefiles, MSYS Makefiles or Ninja, requires running CMake twice for building a project in both `Release` and `Debug` configuration. CMake
however also supports *multiple-configuration* generators. These are usually project files offered by integrated-development environments, most notably Visual Studio and Xcode

```bash
$ cmake .. -G"Visual Studio 12 2017 Win64" -D CMAKE_CONFIGURATION_TYPES="Release;Debug"
$ cmake --build . --config Release
```

#### Controlling compiler flags
Two main approaches:
* CMake treats compile options as properties of targets. Thus, one can set compile options on a per target basis, without overriding CMake defaults.
* You can directly modify the `CMAKE_<LANG>_FLAGS_<CONFIG>` ariables by using the -D CLI switch. These will affect all targets in the project and override or extend CMake defaults.

```cmake
list(APPEND flags "-fPIC" "-Wall")
if(NOT WIN32)
    list(APPEND flags "-Wextra" "-Wpedantic")
endif()

target_compile_options(geometry
    PRIVATE
    ${flags}
)
```
Compile options can be added with three levels of visibility: `INTERFACE`, `PUBLIC`, and `PRIVATE`.
* `PRIVATE`: compile options will only be applied to the
given target and not to other targets consuming it.
* `INTERFACE`: compile options on a given target will only
be applied to targets consuming it.
* `PUBLIC`: compile options will be applied to the given
target and all other targets consuming it.

```bash
$ cmake --build . -- VERBOSE=1
```

```cmake
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions")
    list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wsuggest-final-types" "-Wsuggest-final-methods" "-Wsuggest-ov
    list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
    list(APPEND CMAKE_CXX_FLAGS "-fno-rtti" "-fno-exceptions" "-Qunused-arguments" "-fcolor-diagnosti
    list(APPEND CMAKE_CXX_FLAGS_DEBUG "-Wdocumentation")
    list(APPEND CMAKE_CXX_FLAGS_RELEASE "-O3" "-Wno-unused")
endif()
```

Generator expressions have the form `$<...>`.

With its 3.1 version, CMake introduced a platform- and compiler-
independent mechanism for setting the language standard for C++ and C: setting the `<LANG>_STANDARD` property for targets.

Request all library symbols to be exported on Windows
`set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)`

* `CXX_STANDARD`: mandates the standard that we would like to have.
* `CXX_EXTENSIONS`: tells CMake to only use compiler flags that will enable the ISO C++ standard, without compiler-specific extensions.
* `CXX_STANDARD_REQUIRED`: specifies that the version of the standard chosen is required.

CMake offers an even finer level of control over the language standard by introducing the concept of compile features. `target_compile_features()`

#### control flow constructs
CMake also offers language facilities for creating loops: `foreach-endforeach` and `while-endwhile`. Both can be combined with `break` for breaking from the
enclosing loop early.

```cmake
list(
    APPEND sources_with_lower_optimization
    geometry_circle.cpp
    geometry_rhombus.cpp
)

foreach(_source IN LISTS sources_with_lower_optimization)
    set_source_files_properties(${_source} PROPERTIES COMPILE_FLAGS -O2)
    message(STATUS "Appending -O2 flag for ${_source}")
endforeach()
```

`set_source_files_properties(file PROPERTIES property value)`, sets the property to the passed value for the given file.

`get_source_file_property(VAR file property)`, retrieves the value of the desired property for the given file and stores it in the CMake VAR variable.

In CMake, lists are semicolon-separated groups of strings. A list can be created either by the `list` or the `set` commands. For example, both `set(var a b c d e)` and `list(APPEND a b c d
e)` create the list a;b;c;d;e.

foreach() construct can be used in four different ways
* `foreach(loop_var arg1 arg2 ...)`
* `foreach(loop_var RANGE start stop [step])`
* `foreach(loop_var IN LISTS [list1 [...]])`
* `foreach(loop_var IN ITEMS [item1 [...]])`

Page-120
