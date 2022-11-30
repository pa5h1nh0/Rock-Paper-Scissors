# Building with CMake

## Build

The build was tested on Linux only!  
You need CMake >= 3.10 version and a C++20 compiler.  
This project doesn't require any special command-line flags to build to keep
things simple.

Here are the steps for building in release mode with a single-configuration
generator, like the Unix Makefiles one:

```sh
cmake -S . -B build -D CMAKE_BUILD_TYPE=Release
cmake --build build
```

Configure a Debug build:
```sh
cmake --preset=dev
```

Build in Debug mode and run the executable:
```sh
cmake --build --preset=dev -t run-exe
```

Configure a Release build:
```sh
cmake --preset=prod
```

Build in Release mode and run the executable:
```sh
cmake --build --preset=prod -t run-exe
```

Run unit-tests via `CTest` (less verbose output):
```sh
ctest --preset=dev
```
or directly running the test executable (more verbose output):
```sh
./build/dev/test/visitor_pattern_test
```

## Install

This project doesn't require any special command-line flags to install to keep
things simple. As a prerequisite, the project has to be built with the above
commands already.

The below commands require at least CMake 3.15 to run, because that is the
version in which [Install a Project][2] was added.

Here is the command for installing the release mode artifacts with a
single-configuration generator, like the Unix Makefiles one:

```sh
cmake --install build
```

[1]: https://cmake.org/download/
[2]: https://cmake.org/cmake/help/latest/manual/cmake.1.html#install-a-project
