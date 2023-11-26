# OpenGL

* Windows has graphics API, directX or direct3d.
* Apple uses Matel graphics API

* OpenGL functions are implemnted in graphics driver
* GLEW (OpenGL Extenstion Wrangler) Library which pull the opengl functions from opengl driver and provides all the function prototypes, constants etc


* For building Win32 application using CMake use the following command

```
cmake -S. -Bb -A Win32
cmake --build release --config release  // for release build
```

* There exist both different versions of OpenGL and different variants of OpenGL. For example, in addition to **"standard OpenGL"** (sometimes called "desktop OpenGL"), there exists a variant called **"OpenGL ES"** which is tailored for development of embedded systems
(hence the "ES"). "Embedded systems" include devices such as mobile phones, game consoles, automobiles, and industrial control systems.

* _OpenGL ES_ is mostly a subset of standard OpenGL, eliminating a large number of operations that are typically not needed for embedded systems.

* Another variant of OpenGL is called **"WebGL"**. Based on OpenGL ES, WebGL is designed to support the use of OpenGL in web browsers. WebGL allows an application to use JavaScript to invoke OpenGL ES operations, which makes it easy to embed OpenGL graphics into standard HTML (web) documents

* Mathematics library called GLM.

* SOIL2 library is used for loading and processing texture image files.

* Graphics programming is _shader based_ that is, some of the program is written in a standard language such as C++ or Java for running on the CPU and some is written in a special-purpose shader language
for running directly on the graphics card (GPU).

* There are many graphics libraries in use today, but the most common library for platform independent graphics programming is called **OpenGL (Open Graphics Library)**.

* In 2006 the ARB transferred control of the OpenGL specification to
the _Khronos Group_, a nonprofit consortium which manages not only the OpenGL specification but a wide variety of other open industry standards.

* In 2004, version 2.0 introduced the OpenGL Shading Language (GLSL), allowing "shader programs" to be installed and run directly in graphics pipeline stages.

* In 2009, version 3.1 removed a large number of features that had been deprecated.

* Version 4.0 (in 2010) added a _tessellation_ stage to the programmable pipeline.

* OpenGL doesn't actually draw to a computer screen. Rather, it renders to a frame buffer, and it is the job of the individual machine to then draw the contents of the frame buffer onto a window on the screen.

* One of the most popular options, and the one used in this book, is **GLFW (Graphics Library Framework)**, which has built-in support for Windows, Macintosh, Linux, and other systems.

* GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.

* GLFW is written in C and supports Windows, macOS, X11 and Wayland.

* Extension libraries:
    * Glee,
    * GL9Loader,
    * GLEW (OpenGL Extension Wrangler), and more recently
    * GL3W and
    * GLAD.

* Two math libraries that are frequently used with OpenGL are **_Eigen_** and **_vmath_**.

* **GLM (OpenGL Mathematics)** It is a header-only C++ library compatible with Windows, Macintosh, and Linux.

* Texture loading libraries
    * FreeImage,
    * DevIL,
    * OpenGL Image (GLI), and
    * Glraw.

* Probably the most commonly used OpenGL image loading library is **Simple OpenGL Image Loader (SOIL)**, although it has become somewhat outdated.

* On the hardware side, OpenGL provides a multi-stage graphics pipeline that is partially programmable using a language called **GLSL (OpenGL Shading Language)**.

* One important task of a C++/OpenGL application is to install the programmer's GLSL code onto the GPU.

* There are other shader languages, such as **High-Level Shader Language (HLSL)**, which works with Microsoft's 3D framework DirectX.

* OpenGL is capable of drawing only a few kinds of very simple things, such as _points_, _lines_, or _triangles_. These simple things are called primitives.

* OpenGL still requires that at least one **VAO (Vertex Array Objects)** be created whenever shaders are being used, even if the application isn't using any buffers. So the two lines create the required VAO.

```c++
glGenVertexArrays(numVAOs, vao);
glBindVertexArray(vao[0]);
```

* The programmable **tessellation** stage is one of the most recent additions to OpenGL (in version 4.0). It provides a tessellator that
can generate a large number of triangles, typically as a grid, and also some tools to manipulate those triangles in a variety of ways.

* Whereas the _vertex shader_ gives the programmer the ability to manipulate _one vertex at a time_ (i.e., "per vertex" processing), and the _fragment shader_ (as we will see) allows manipulating _one pixel at a time_ ("per-fragment" processing), the _geometry shader_ provides the capability to manipulate _one primitive at a time_ - "per-primitive" processing.

* Our 3D world of vertices, triangles, colors, and so on needs to
be displayed on a 2D monitor. That 2D monitor screen is made up of a **raster** - _a rectangular array of pixels_.

* The purpose of the fragment shader is to assign colors to the rasterized pixels.

* **Hidden surface removal (HSR)**. OpenGL can perform a variety of HSR operations, depending on the effect we want in our scene.

* Hidden surface removal is accomplished by OpenGL through the cleverly
coordinated use of two buffers: the color buffer (which we have discussed previously), and the depth buffer (sometimes called the Z-buffer).

* Points in **homogeneous notation** contain four values. The first three correspond to X, Y, and Z, and the fourth, W, is always a fixed nonzero value, usually 1.

* There are two ways of sending data through the OpenGL pipeline:
    * through a _buffer_ to a vertex attribute or
    * directly to a _uniform variable_.

* **OpenGL** is a purebred _graphics API_, and this means that it doesn’t deal with anything other than 2D and 3D graphics. **DirectX**, on the other hand, is a _collection of graphics, audio, networking_, and other hardware APIs that all work together.

* **OpenGL** is a free API managed by a non-profit company called _Khronos Group_.

* **DirectX** is made by Microsoft. DirectX works on Windows and Xbox primarily.

* **Uniform** is a way to transfer data from CPU to shader (GPU). Also vertex buffer can be used for same purpose.

* If a uniform is not used in the shareder, OpenGL might

* OpenGL added _vertex arrays_ so that a single draw command with fairly low CPU overhead gets amplified into a lot of GPU work.

* The “bindless” family of extensions
allows the GPU to reference buffers and textures directly rather than going through
expensive binding calls in the driver.

* AZDO (Approaching Zero Driver Overhead)

* GPUs are also extremely
flexible, and are able to work on tasks that might not be considered graphics at all, such
as physical simulations, artificial intelligence, and even audio processing.

* Current GPUs consist of large numbers of small programmable processors called _shader cores_ that run mini-programs called **shaders**.

* in 2008, the ARB decided it would "fork" the OpenGL specification into two profiles. The first is the modern, **core profile**, which _removes a number of legacy features_, leaving only those that are truly accelerated by current graphics hardware.

* The **compatibility profile** maintains backward compatibility with all revisions of OpenGL back to version 1.0

# Learning OpenGL

* OpenGL is basically one large state machine,

* An object in OpenGL is a collection of options that represents a subset of OpenGL’s state.

```c++
// Typical OpenGL setup

// create object and get its ID
uint32_t obId {};
glGenObject(1, &objId);                  // generate object
glBindObject(GL_WINDOW_TARGET, objId);   // bind/assign object to context
glSetObjectOption(GL_WINDOW_TARGET, GL_OPTION_WINDOW_WIDTH, 800);


// unbind/set context target back to default
glBindObject(GL_WINDOW_TARGET, 0);
```

* we have to create a window, define a context, and handle user input all by ourselves. Some of the more popular libraries are GLUT, SDL, SFML and GLFW

* GLFW is a library, written in C, specifically targeted at OpenGL. It allows us to create an OpenGL context, define window
parameters, and handle user input, which is plenty enough for our purposes.

* CMake is a tool that can generate project/solution files of the user’s choice

#### Compile GLFW as using Visual Studio 17 2022

```
glfw-3.3.8> cmake -H\. -Bbuild
glfw-3.3.8> cmake --build build

// To check if a static library is 64 bit or 32 bit use the below command
dumpbin glfw3.lib /headers | findstr machine
```

* CMake automatically configured the solution so it compiles to a 64-bit library;

* By default, CMake generate a debug build

* Note that the 64-bit equivalent of the OpenGL library is called `opengl32.lib`, just like the 32-bit equivalent, which is a bit of an
unfortunate name.

* For Linux users compiling with GCC, the following command line options may help you compile the project

```
 -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl.
```

* Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time. Thankfully, there are libraries for this purpose as well where **GLAD** is a popular and up-to-date library.

* GLAD has a slightly different configuration setup than most common open source libraries. GLAD uses a
web service3 where we can tell GLAD for which version of OpenGL we’d like to define and load all
relevant OpenGL functions according to that version.

* Telling GLFW we want to use the core-profile means we’ll get access to a
smaller subset of OpenGL features without backwards-compatible features

* GLAD manages function pointers for OpenGL so we want to initialize GLAD before we call any OpenGL function.

* processed coordinates in OpenGL are between -1 and 1
so we effectively map from the range (-1 to 1) to (0, 800) and (0, 600).

* A color buffer is a large 2D buffer that contains color values for each pixel in GLFW’s window

* An iteration of the render loop is more commonly called a **frame**.

* We can clear the screen's color buffer using `glClear` where we pass in buffer bits to specify which buffer we would like to clear. possible bits we can set are

```
GL_COLOR_BUFFER_BIT
GL_DEPTH_BUFFER_BIT
GL_STENCIL_BUFFER_BIT

glClearColor() // is a state setting function
glClear()      // is a state-using function
```

* In OpenGL everything is in _3D space_, but the screen or window is a 2D array of pixels so a large part
of OpenGL's work is about transforming all 3D coordinates to 2D pixels that fit on your screen.

* The graphics pipeline takes as input a set of 3D coordinates and transforms these to colored 2D pixels on your screen.

* The processing cores run small programs on the GPU for each step of the pipeline. These small programs are called **_shaders_**. Shaders are written in the OpenGL Shading Language (GLSL)

* The first part of the pipeline is the **vertex shader** that takes as input a single vertex. The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates.

* A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

* In modern OpenGL we are required to define at least a vertex and fragment shader of our own
(there are no default vertex/fragment shaders on the GPU).

* OpenGL only processes 3D coordinates when they're in a specific range between `-1.0` and `1.0` on all 3 axes (x, y and z). All coordinates within this so called **normalized device coordinates (NDC)** range will end up visible on your screen

* vertex buffer objects (VBO) can store a large number of vertices in the GPU's memory.

* OpenGL has many types of buffer objects and the buffer type of a vertex buffer object is `GL_ARRAY_BUFFER`.

* `glBufferData` is a function specifically targeted to copy user-defined data into the currently bound buffer.

* How graphics card should manage the bound data

```
GL_STREAM_DRAW    // the data is set only once and used by the GPU at most a few times.
GL_STATIC_DRAW:   // the data is set only once and used many times.
GL_DYNAMIC_DRAW:  // the data is changed a lot and used many times.
```

* A vector in GLSL has a maximum size of 4 and each of its values can be retrieved via `vec.x`, `vec.y`, `vec.z` and `vec.w` respectively where each of th em represents a coordinate in space. The `vec.w` component is not used as a position in space but is used for something called **perspective division**.























* Vertex buffer - layout of the vertex buffer
  index buffer
  shader

  bind shader
  bind vertex array
  bind index buffer
  issue draw call

  opengl compatibility profile
  opengl core profile

  opengl pipeline
  vertex shader -> geometry shader -> rasterization -> fragment shader

  different primitives => points, lines, triangles and quads

  immediate mode progarmming => draw graphics to screen one frame at a time.

  write own shader using OpenGL Shading Language (GLSL)

  transormation => manipulate position, orientation and size of objectes in 3D space.

  Vertex Buffer Object (VBO) require extra work

  WPF: Windows Presentation Foundation is a UI framework for creating desktop application. WPF uses Extensible Application Markup Language (XAML) to provide declarative model for application programming.

  REST (Representatonal State Transfer)
  REST is a set of architectural constraints, not a protocol or a standard.

Sync vs Async programming model
Async: non-blocking architecture
Sync: blocking architecture

Design pattern: generic reusable soltuion to commonly occurring problems within a given context in software design

Creational design pattern
Abstract Factory
Builder
Factory Method
Prototype
Singleton

Structural design pattern
Adapter
Bridge
Composite
Facade
Flyweight
Proxy
Decorator

Behavioural design pattern
Chain of Responsibility
Command
Interpreter
Iterator
Mediator
Memento
Observer
State
Strategy
Templete
Method
Visitor

abstraction: hiding internal details of an application from outside world. It is used to describe things in simple terms. manage complexity

Abstraction: showing only essential attributes and hiding unnecessary information.
Encapsulation: information hiding
Encapsulation is a process of wrapping the data and the code, that operate on the data into a single entity.

mt19937-based generator, which employs a 32-bit Mersenne Twister algorithm with a
state size of 19937 bits.

Video encoder : take video signal (upto 3 gigabit/sec for HD) 1 Mbps.
Compression standard: H.264 (1000/1)
HVAC h.265 standard (twice as effective)


Shader Languages
* C for graphics (Cg): developed by Nvidia graphics company. Cg compilers can output shader programs supported by both DirectX and OpenGL

* High Level Shading Lanaguage (HLSL): developed by Microsoft Corporation for use with DirectX graphics API. Since the release, DirectX 12 the HLSL language supports even lower level hardware control and has seen dramatic performance improvements.

* OpenGL Shading Language (GLSL) is a shading language based on C. It was created by **OpenGL Architecture Review Board** (OpenGL ARB) to give developers more direct control of the graphics pipeline without having to use ARB assmbly language or other hardware specific languages.

* Most modern shader programs are composed of up to five different types of sharder files:
    * fragment or pixel shaders
    * vertex shaders
    * geometry shaders
    * compute shaders
    * tessellation shaders
