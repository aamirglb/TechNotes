# conan

* Conan is a dependency and package manager for C /C++ language. 

* C/C++ open source libraries: _folly_, _boost_, _openssl_, _abseil_

* The Conan package manager makes handling external dependencies easier and also improves the deployment process of packages.

* conan recipe capture build instruction for the project for any build system on any platform

* pkg/0.1@user/channel => **recipe reference**

* options + settings are hash to produce unique id called **package id**

* Conan hashes together "options" and "settings" to calculate a unique value for each binary package.

* conan-center-index on github as package recipe

* Binary build service runs recipe to build binary package

    ```bash
    git clone https://github.com/conan-io/training
    cd training/docker_environment
    docker-compose up -d
    docker exec -it conan-training bash
    ```

    ```bash
    conan install ..  // release
    conan install .. -s build_type=Debug
    cmake .. -DCMAKE_BUILD_TYPE=Debug
    cmake --build .
    ```

* gcc compiler arg format??

* The conan install command reads a conanfile in the local directory, downloads dependencies for it, and produces information about those dependencies in a file for the build system.

    ```bash
    conan --help
    conan remote list
    conan remove "*" -f
    ```

* To generate a recipe for sample "hello world" package

    ```bash
    mkdir conan_tutorial && cd conan_tutorial
    conan new hello/0.1 -t -s
    ```

* By setting generators = "cmake", Conan generates a _conanbuildinfo.cmake_ file that can be included when we build the package with **CMake**.

* The `exports_sources = src/*` is indicating to Conan to copy all the files from the local _src/_ folder to the local Conan cache when exporting _conanfile.py_. 

* The advantage of the approach is it makes the recipe self-contained and will not need to get the sources from external locations when building from sources.

* `conanfile.py` usually have following methods

    ```python
    from conans import ConanFile, CMake

    class HelloConan(ConanFile):
        name = "hello"
        version = "0.1"
        license = "
        author = ""
        url = ""
        description = ""
        topics = ""
        settings = "os", "compiler", "build_type", "arch"
        options = {"shared": [True, False]}
        default_options = {"shared": False}

        # generates conanbuildinfo.cmake
        generators = "cmake"

        # copy all files to local conan cache when exporting
        exports_sources = "src/*"


        def build(self):
            cmake = CMake(self)
            cmake.configure(source_folder="src")
            cmake.build()

            # Explicit way to run
            #self.run('cmake %s/hello %s' % (self.source_folder, cmake.command_line))
            #self.run("cmake --build . %s" % cmake.build_config)

        # copy build artefacts to package folders under conan local cache
        def package(self):
            self.copy("*.h", dst="include", src="src")
            self.copy("*.lib", dst="lib", keep_path=False)
            self.copy("*.dll", dst="bin", keep_path=False)
            self.copy("*.dylib*", dst="lib", keep_path=False)
            self.copy("*.so", dst="lib", keep_path=False)
            self.copy("*.a", dst="lib", keep_path=False)

        # buld information
        def package_info(self):
            self.cpp_info.libs = ["hello"]

        
    ```

```bash
conan export . demo/testing
conan search
```

* edit ~/.conan/profiles/default => set compiler.libcxx=libstdc++11