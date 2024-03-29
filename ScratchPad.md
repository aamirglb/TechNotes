Pragmatic: Concerned with practical matters
           Guided by practical experience and observation rather than theory

# The Pragmatic Programmer

Tip-1: Care About Your Craft
Tip-2: Think! About your work
Tip-3: You have agency - You can change your organization or change your organization
Tip-4: Provide options, don't make lame excuses
Tip-5: Don’t Live with Broken Windows - Don’t leave "broken windows" (bad designs, wrong decisions, or poor code) unrepaired.
Tip-6: Be a Catalyst for Change
Tip-7: Remember the Big Picture
Tip-8: Make Quality a Requirements Issue
Tip-9: Invest Regularly in Your Knowledge Portfolio
Tip-10: Critically Analyze What You Read and Hear
Tip-11: English is Just Another Programming Language
Tip-12: It's Both What You Say and the Way You Say It
Tip-13: Build Documentation In, Don’t Bolt It On
Tip-14: Good Design Is Easier to Change Than Bad Design
Tip-15: DRY - Don't Repeat Yourself
Tip-16: Make It Easy to Reuse
Tip-17: Eliminate Effects Between Unrelated Things
Tip-18: There Are No Final Decisions
Tip-19: Forgo Following Fads
Tip-20: Use Tracer Bullets to Find the Target
Tip-21: Prototype to Learn
Tip-22: Program Close to the Problem Domain
Tip-23: Estimate to Avoid Surprises
Tip-24: Iterate the Schedule with the Code
Tip-25: Keep Knowledge in Plain Text (HTML, JSON, YAML, HTTP, SMTP, IMAP) 
Tip-26: Use the Power of Command Shells
Tip-27: Achieve Editor Fluency 
Tip-28: Always Use Version Control
Tip-29: Fix the Problem, Not the Blame 
Tip-30: Don't Panic
Tip-31: Failing Test Before Fixing Code
Tip-32: Read the Damn Error Message
Tip-33: "select" Isn't Broken
Tip-34: Don't Assume It - Prove It
Tip-35: Learn a Text Manipulation Language [sed, awk, perl]
Tip-36: You Can't Write Perfect Software
Tip-37**: Design with Contracts (DBC)
Tip-38: Crash Early
Tip-39: Use Assertions to Prevent the Impossible
Tip-40: Finish What You Start (Deallocate resource)
Tip-41: Act Locally
Tip-42: Take Small Steps - Always
Tip-43: Avoid Foutune-Telling
Tip-44: Decoupled Code Is Easier to Change
Tip-45: Tell, Don't Ask
Tip-46: Don't Chain Method Calls
Tip-47: Avoid Global Data
Tip-48: If It's Important Enough to Be Global, Wrap It in an API
Tip-49: Programming Is About Code, But Programs Are About Data
Tip-50: Don't Hoard State, Pass It Around
Tip-51: Don't Pay Inheritance Tax
Tip-52: Prefer Interfaces to Express Polymorphism
Tip-53: Delegate to Services: Has-A Trumps Is-A
Tip-54: Use Mixins to Share Functionality
Tip-xx: 

* The greatest of all weaknesses is the fear of apprearing weak.

* Entropy is a term from physics that refers to the amount of "disorder" in a system.
Unfortunately, the laws of thermodynamics guarantee that the entropy in the universe tends toward a maximum.

* When disorder increases in software, we call it "software rot." (more optimistic term: "technical debt")

* hopelessness can be contagious, neglect accelerates the software rot faster than any other factor.

* Great software today is often preferable to the fantasy of perfect software tomorrow.

* Don't spoil a perfectly good program by overembellishment and overrefinement. Move on, and let your code stand in its own right for a while.

* software that suffers from feature bloat

* An investment in knowledge always pays the best interest. -- Benjamin Franklin

* Your ability to learn new things is your most important strategic asset. But how do you learn how to learn, and how do you know what to learn?

* Learn at least one new language every year 

* Read a technical book each month

* A good idea is an orphan without effective communication.
* The meaning of your communication is the response you get

* Pragmatic Programmers embrace documentation as an integral part of the overall development process.

* ETC principle: Easier to Change.

* Every piece of knowledge must have a single, unambiguous, authoritative representation within a system

* Object-Oriented Software Construction [Mey97],

* the term "orthogonality" has come to signify a kind of independence or decoupling. Two or more things are orthogonal
if changes in one do not affect any of the others

* Two or more things are orthogonal if changes in one do not affect any of the others.

* helicopters have four basic controls.
1) The _cyclic_ is the stick you hold in your right hand. Move it, and the helicopter moves in the corresponding direction.
2) Your left hand holds the _collective_ pitch lever. Pull up on this and you increase the pitch on all the blades, generating lift.
3) At the end of the pitch lever is the _throttle_.
4) Finally you have two _foot pedals_, which vary the amount of tail rotor thrust and so help turn the helicopter.

Decorator Pattern: adding functionality to things without changing them.

your code is easier to understand and maintain if you explicitly pass any required context into your modules.

In object-oriented applications, context is often passed as parameters to objects' constructors. In other code, you can create
structures containing the context and pass around references to them.

* The term _tracer bullet development_ refer to visually illustrate the need for immediate feedback under actual conditions with a moving goal.

* Human-readable forms of data, and self-describing data, will outlive all other forms of data and the applications thats created them.

* Bertrand Meyer (Object-Oriented Software Construction) developed the concept of _Design by Contract_ for the language **Eiffel**.
    * Preconditions
    * Postconditions
    * Class invariants

* Don't use assertions in place of real error handling. Assertions check for things that should never happen.

* In the _Observer Pattern_, we have a source of events, called the _observable_ and a list of clients, the _observers_, who are interested in those events.

* Publish/Subscribe (pubsub) generalizes the observer pattern, at the same time solving the problems of coupling and performance.

* Inheritance first appeared in __Simula 67__ in 1969.

* Three techniques that to replace inheritance
    * Interfaces and protocols
    * Delegation
    * Mixins and traits

* Mixin: The basic idea is simple: we want to be able to extend classes and objectes with new functionality without using inheritance.

#### Read-World Domain Language
* RSpec is a testing library for Ruby.
* Cucumber is a programming language neutral way of specifying tests.
* Phoenix Routes - Web framework for mapping incoming HTTP requests onto handler functions in the code.
* Ansible is a tool that configures software, typically on a bunch of remote servers.

* An object is a region of memory with a type that specifies what kind of information can be placed in it. A named object is called a variable.

* End-of-input character: (end of file) - On a Windows machine, that's Ctrl+Z followed by an Enter. On a Unix or Linux machine that's Ctrl+D.

# Code Complete
================

* "Coding" isn't really the best word because it implies the mechanical translation of a preexisting design into a computer language; construction is not at all mechanical and involves substantial creativity and judgment

* In many projects, the only documentation available to programmers is the code itself.

* The most challenging part of programming is conceptualizing the problem, and many errors in programming are conceptual errors

* Fred Brooks’s The Mythical Man-Month

* A good craftsman knows the right tool for the job and knows how to use it correctly. 

* Measure Twice, Cut Once

* The acronym "Cobol" stands for COmmon Business-Oriented Language. 

* "Fortran" stands for FORmula TRANslation




C++
===
* `std::enable_if_t<condition, type>` evaluates to type if condition is true. Otherwise, the std::enable_if_t expression does not evaluate to
anything.

* When the compiler sees different template functions with the same name and has to choose one of them, an important principle comes into play: **SFINAE**, which stands for _Substitution Failure is not an Error_. In this case, this means that the compiler does not
error out if the return value of one of those functions cannot be deduced from an erroneous template expression (which std::enable\_if is, in case its condition evaluates to false).  It will simply look further and try the other function implementation. That is the trick; that is
how this works.

If we use `std::unordered_map` instead of `std::map`, we have a different degree of freedom for the choice of the key type which shall be used.

`std::unordered_map` because it will not distinguish items via their smaller/greater ordering relationship but via hash values. The
only thing we need to do is to implement a hash function for our own type, and an equal to == operator implementation, which tells whether two objects are identical

coroutines: suspend and resume with state preservation
A concept is a set of requirements on a set of template arguments.
A concept is a compile-time predicate

diamond of death pattern in the class hierarchy

With virtual inheritance, we can make sure that a parent class only appears in any children classes once. To implement virtual inheritance, we simply use the virtual keyword when declaring the class we want to inherit from.

The first potential drawback is that all templates must have their
entire implementation in the same file, usually the header.

OpenGL
======

For building Win32 application using CMake use the following command
cmake -S. -Bb -A Win32
cmake --build release --config release  // for release build


there exist both different versions of OpenGL and different variants of OpenGL. For example, in
addition to "standard OpenGL" (sometimes called "desktop OpenGL"), there exists a
variant called "OpenGL ES," which is tailored for development of embedded systems
(hence the "ES"). "Embedded systems" include devices such as mobile phones, game
consoles, automobiles, and industrial control systems. OpenGL ES is mostly a subset of
standard OpenGL, eliminating a large number of operations that are typically not needed
for embedded systems.


another variant of OpenGL is called "WebGL" Based on OpenGL ES, WebGL is
designed to support the use of OpenGL in web browsers. WebGL allows an application to
use JavaScript1 to invoke OpenGL ES operations, which makes it easy to embed OpenGL
graphics into standard HTML (web) documents

mathematics library called GLM.

SOIL2 library is used for loading and processing texture image files.

graphics programming is _shader based_ that is, some of the program is written in a standard language such as C++
or Java for running on the CPU and some is written in a special-purpose shader language
for running directly on the graphics card (GPU).

There are many graphics libraries in use today, but the most common library for platfor mindependent
graphics programming is called OpenGL (Open Graphics Library).

In 2006 the ARB transferred control of the OpenGL specification to
the Khronos Group, a nonprofit consortium which manages not only the OpenGL
specification but a wide variety of other open industry standards.

In 2004, version 2.0 introduced the OpenGL Shading Language (GLSL), allowing "shader programs" to be installed and run directly in graphics pipeline stages.

In 2009, version 3.1 removed a large number of features that had been deprecated,

version 4.0
(in 2010) added a _tessellation_ stage to the programmable pipeline.

OpenGL doesn't actually draw to a computer screen. Rather, it renders to a
frame buffer, and it is the job of the individual machine to then draw the contents
of the frame buffer onto a window on the screen.

One of the most popular options, and the one used in this book, is GLFW (Graphics Library Framework),
which has built-in support for Windows, Macintosh, Linux, and other systems

GLFW is an Open Source, multi-platform library for OpenGL, OpenGL ES and Vulkan development on the desktop. It provides a simple API for creating windows, contexts and surfaces, receiving input and events.
GLFW is written in C and supports Windows, macOS, X11 and Wayland.

Extension libraries:
Glee,
GLLoader,
GLEW (OpenGL Extension Wrangler), and
more recently GL3W and GLAD.

Two math libraries that are frequently used with OpenGL are Eigen and vmath,

GLM (OpenGL Mathematics). It is a header-only C++ library compatible
with Windows, Macintosh, and Linux

Texture loading libraries
FreeImage,
DevIL,
OpenGL Image (GLI), and
Glraw.

Probably the most commonly used OpenGL image loading library is Simple OpenGL Image Loader (SOIL), although it has
become somewhat outdated.

On the hardware side, OpenGL provides a multi-stage graphics pipeline that is partially programmable using a language called GLSL (OpenGL Shading
Language).

One important task of a C++/OpenGL application is to install the programmer’s GLSL code onto the GPU.

There are other shader languages, such as HLSL, which works with Microsoft's 3D framework DirectX.

OpenGL is capable of drawing only a few kinds of very simple things, such as points, lines, or triangles. These simple things
are called primitives,

OpenGL still requires that at least one VAO (Vertex Array Objects) be created whenever shaders are being used, even if the application isn't
using any buffers. So the two lines create the required VAO.


The programmable tessellation stage is one of the most recent additions to OpenGL (in version 4.0). It provides a tessellator that
can generate a large number of triangles, typically as a grid, and also some tools to manipulate those triangles in a variety of ways

Whereas the vertex shader gives the programmer the ability to manipulate one vertex at a time (i.e., "pervertex" processing), and the fragment shader (as we will see) allows manipulating
one pixel at a time ("per-fragment" processing), the geometry shader provides the capability to manipulate one primitive at a time "per-primitive" processing.

our 3D world of vertices, triangles, colors, and so on needs to be displayed on a 2D monitor. That 2D monitor screen is made up of a raster - a rectangular array of pixels.

the purpose of the fragment shader is to assign colors to the rasterized pixels.

hidden surface removal, or HSR. OpenGL can perform a variety of HSR operations, depending on the effect we want in our scene.

Hidden surface removal is accomplished by OpenGL through the cleverly coordinated use of two buffers: the color buffer (which we have discussed
previously), and the depth buffer (sometimes called the Z-buffer).

Points in homogeneous notation contain four values. The first three correspond to X, Y, and Z, and the fourth, W, is always a fixed nonzero value, usually 1.

OpenCV
======

OpenCV is an open source library containing more than 500 optimized
algorithms for image and video analysis.

OpenCV was originally developed at Intel

1999 - Started
2006 - version 1.0
2009 - version 2.0 introduce c++ interface
2012 - non-profit foundation
2013 - version 3.0 (improve usability of library, large module split into smaller one)

* opencv\_core module that contains the core functionalities of the library, in
particular, basic data structures and arithmetic functions

* opencv\_imgproc module that contains the main image-processing
functions

* opencv\_highgui module that contains the image and video reading and
writing functions along with some user interface functions

* opencv\_features2d module that contains the feature point detectors and
descriptors and the feature point matching framework

* opencv\_calib3d module that contains the camera calibration, two-view
geometry estimation, and stereo functions

* opencv\_video module that contains the motion estimation, feature
tracking, and foreground extraction functions and classes

* opencv\_objdetect module that contains the object detection functions
such as the face and people detectors

machine learning functions (opencv\_ml),
computational geometry algorithms (opencv\_flann),
contributed code (opencv\_contrib)
opencv\_photo for computational photography
opencv\_stitching for image-stitching algorithms


old notes
----------
packages required for opencv
key libraries used by opencv

build-essential
cmake
git
pkg-config

libraries reading image format
libjpeg8-dev
libtiff5
libjasper-dev
libpng12-dev

video codec format
libavcodec-dev
libavformat-dev
libswscale-dev
libv4l-dev

user interface feature
libgtk2.0-dev

optimize opencv command
libatlas-base-dev
gfortran

Core Concepts
=============

C:\Users\Aamir\AppData\Local\Programs\Python\Python37\Lib\site-packages\numpy\core\include

OpenCV 4.3.0 build failing on generating `vs_version.rc` using mingw-w64
Ans: Hi @alalek adding the `-DOPENCV_ALLOCATOR_STATS_COUNTER_TYPE=int64_t` option to CMAKE allows the build to complete.

dense multidimensional array, Mat
Image Process include
* filtering (linear and nonlinear)
* geometric transformations
* color space conversion ...

machine learning tools such as
* statistical classification
* regression
* data clustering

OpenCV Mat class is used for dense n-dimensional single or multichannel array.

Given an image matrix, we can find the derivative using another matrix called maskor kernel.

Python for Microscopists by Sreeni

Popular Linux Desktop Environments:
1. GNOME Shell
2. KDE Plasma Desktop
3. LXQt
4. Cinnamon
5. MATE
6. Xfce

tree -L 1
htop

Bash, Zsh, csh, fish and ksh

BusyBox alternative to GNU coreutils (its a single program)

Filesysten Huerarchy Standard (FHS)

/etc system configuration
/var changable variable system information stored like logs
dev, proc, sys -> created by kernel

chmod chrgrp

SELinux AppArmor

Package managers: ATP, dnf, apk, zypper
System manager - systemd or SysVinit
Debian doesn't include sudo (but can be installed)

cat /etc/*release

Arch or Alpine Linux
List of Linux distributions (wikipedia)


kuler.adobe.com
/etc/wsl.conf
[network]
name=myWSL

wslpath -> convert path between Windows and Linux


C# and .Net Essential Programming
=================================
dotnet --version
dotnet --list-sdks

Free, cross-platform, open-source developer platform
.NET provides:
Core Services
Languages
CLR

Create new console app
dotnet new console -n <appname> -f <dotnet platform> "net6.0"

starting with .net6 some common library are automatically included
implicit using directives

using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Threading;
using System.Threading.Tasks;

Value Types: enum, structs and tuples
Reference Types: objects, strings and records

String methods:
Strings are inmutable

Equals
Compare
Join('c', );
Join("string");
Replace();
Contains();

dotnet workload search
dotnet workload list
dotnet workload install
dotnet workload update
dotnet workload repair

Base Class Library (BCL)
NuGet Package Management (Modular functionality)

C# 10.0
=======
Namespace Management
global using System.Text.RegularExpression


Linux Kernel
============

kernel name like vmlinuz-<KERNEL VERSION>
boot loader, like GRUB

virtual file systems:
* proc
* sys
* debugfs

Loadable kernel modules

Commands for HW info
--------------------
lshw and lspci
lsusb and lsbk
lscpu and lsdev

Linux system call list: include/uapi/asm-generic/unistd.h

documented in man section 2
!$: last output of last line

man 1: user commands
man 2: linux programmer's manual

`printk()` is kernel's function for code to print message - sent to RAM buffer
sysctl -a


GStreamer
==========

GStream: multimedia framework (for media application)
to get access to graphics hardware (codec shipped with intel cpu, integrated graphics)
gstreamer has plugin architecutre

Intel Media SDK for Intel Graphics Hardware
Scriptable Command Line Tools

gst-inspect
gst-launch
gst-editor

CUDA core is a technology from NVidia. Allows using GPU hardware as generic computer.

gst-discover => gives information about the file

Transcode => un-encode -> process -> decode

.NET-6 Deep Dive
================



C++ Design Patterns: Behavioral
===============================

Design Pattern: Solution to very common problems in object oriented programming (in code organization)
anti-patterns: harmful pattern


12 Behavioral Design Patterns
1. Chain of Responsibility
1. Command
1. Mediator
1. Observer
1. Interpreter
1. State
1. Strategy
1. Template Method
1. Visitor
1. Iterator
1. Memento
1. Null-Object


C++ Concurrent Programming
==========================

Flynn's Taxonomy - Parellel hardware Clasifying multip processor architecture
SISD  Single Instruction Single Data
SIMD  Single instruction multiple data (GPU USES simd)
MISD  Multiple instruction single data
MIMD  Multiple instruction multiple data (most important)

SPMD: single program multiple data
MPMD: multiple program multiple data

shared memory: All processors share same memory
distrubuted memory:

Concurrency           vs   Parallelism
Program structure          Simultaneous execution

Preemptive vs non preemptive schecduling algorithm

data race:
The operation to aquire a mutex is atomic operation
atomic operation is uninterrupted

reenterant or recursive mutex

reader-writer lock

shared mutex - technically uses more resources
shared read by multiple threads at once
exclusive write - only one thread at a time

```cpp
std::shared_mutex marker
marker.lock_shared();    // shared read lock
marker.unlock_shared();

marker.lock();     // exclusive write lock
marker.unlock();
```

# CMake
* CMake and its siblings, CTest, CPack and CDash leading toolset for building software from source.

* CMake's goal was to provide a set of tools that would make it easier to configure, build, test, and deploy the same project across different platforms.

* CMake is a _build-system generator_, offering a powerful domain-specific language (DSL) to describe what the build system should achieve.

* The __Ninja__ program is a different build-automation tool that works on GNU/Linux, macOS and Windows. Ninja is a new build tool, with a focus on speed, especially for incremental rebuilds.

# Linux Command Line

* To see the current amount of free space on disk: `df -h`

* To display the amount of free memory: `free`

* cd shortcuts
```
cd # changes the working directory to home directory
cd - # Changes the working directory to previous working directory
cd ~user_name # Changes the working directory to home directory of user_name
```
![cd_shortcuts](./images/linux_cmd_line/cd_shortcuts.png)
![ls_shortcuts](./images/linux_cmd_line/ls_shortcuts.png)


* ls ~ /usr - We can specify multiple directories to ls

* ls options:
-l long format output
-t sort the result by file's modification time
--reverse to reverse the order of sort

* Use `file` command to determine a file's type.

* The `less` command is a program to view text file.

* The less program was designed as an improved replacement of an earlier Unix program called more

a symbolic link (also known as a soft link or symlink). In most Unix-like systems, it is possible to
have a file referenced by multiple names.

* `Nautilus` file manager for GNOME
* `Dolphin` and `Konqueror` - File manager for KDE.

* Hard links are the original Unix way of creating links, compared to symbolic
* Hard links have two important limitations.
    * A hard link cannot reference a file outside its own file system. This means a link cannot reference a file that is not on the same disk partition as the link itself.
    * A hard link may not reference a directory.

* Symbolic links create a special type of file that contains a text pointer to the referenced file or directory.
links, which are more modern

* `type` - Display a command's type (external/shell builtin etc)

* `which` - Display an executable's location (which only works for executables)

* `whatis` - Display one line manual page descriptions

* The GNU Project provides an alternative to man pages for their programs, called _info_

* The gzip package includes a special version of _less_ called _zless_ that will display the contents of gzip compressed text files

* It's possible to put more than one command on a line by separating each command with a semicolon

* `alias foo='cd /usr; ls; cd -'`

* `unalias foo`

* if we ever need to actually truncate a file (or create a new, empty file), we can use a trick `> out.txt`

* Redirecting Standard Output and Standard Error to One File `ls -l /usr/bin > output.txt 2>&1`

* Recent versions of bash provide a second, more streamlined method `ls -l /usr/bin &> output.txt`
`ls -l /bin/usr &>> out.txt`

* wildcards always expand in sorted order

* The _uniq_ command is often used in conjunction with _sort_ command. _uniq_ accepts a sorted list of data from either standard input or a single filename argument and, by default, removes any duplicates from the list.

* grep is a powerful program used to find text patterns within files

* The head command prints the first 10 lines of a file, and the tail command prints the last 10 lines.

* tail has an option that allows you to view files in real time. `tail -f /var/log/messages`

* Linux provides a command called tee that creates a "tee" fitting on our pipe. The tee program reads standard input and copies it to both standard output (allowing the data to continue down the pipeline) and to one or more files.

* `ls /usr/bin | tee ls.txt | grep zip`

* echo is a shell builtin that performs a very simple task. It prints its text arguments on standard output

* The shell allows arithmetic to be performed by expansion `$((expression))`

* Perhaps the strangest expansion is called _brace expansion_. With it, you can create multiple text strings from a pattern containing braces

```
echo Front-{A,B,C}-Back
Front-A-Back Front-B-Back Front-C-Back

echo Number_{1..5}
echo {01..15}
```

* Command substitution allows us to use the output of a command as an expansion. `echo $(ls)` `ls -l $(which cp)`

* Adding the -e option to echo will enable interpretation of escape sequences. You can also place them inside $' '.

* _bash_ uses a library (a shared collection of routines that different programs can use) called **Readline** to implement command line editing.

* To find out information about your identity, use the id command.

![arithmetic-expression](./images/linux_cmd_line/arithmetic_expression.png)

![wild-card](./images/linux_cmd_line/wildcard.png)

![wild-card-examples](./images/linux_cmd_line/wildcard_example.png)

![char-class](./images/linux_cmd_line/char_class.png)

![cp-options](./images/linux_cmd_line/cp_options.png)

![cursor-movement](./images/linux_cmd_line/cursor_movement.png)

![less-command](./images/linux_cmd_line/less_command.png)

![man-page](./images/linux_cmd_line/man_page.png)

![mv-options](./images/linux_cmd_line/mv_option.png)

![rm_options](./images/linux_cmd_line/rm_option.png)

![text-editiong](./images/linux_cmd_line/8-2.text-editing.png)

![cut-paste](./images/linux_cmd_line/8-3.cut-paste.png)

![history-command](./images/linux_cmd_line/8-5.history-command.png)

a namespace is
a declaration that provides scope for all the variables, types, and functions inside of its
encapsulation.

What makes
inheritance even more powerful is the fact that we not only can adopt the functions of the
inherited class, we can override them with our own implementations.

The protectd 
methods and variables are only available to the class itself and any classes derived.

With
virtual inheritance, we can make sure that a parent class only appears in any children
classes once.

```
class Boss : public virtual Enemy {}
class FlyingEnemy : public virtual Enemy {}
class FlyingBoss : public Boss, public FlyingEnemy {}  // only one copy of Enemy class
```

polymorphism is the ability to use an object of a class as if it was part of another
class.

By default, const objects
cannot call non const functions. However, non non objects can still call const functions.

the list container does not store
all its elements in one large contiguous block of memory. Instead, it stores its elements as
nodes in a doubly linked list.

Unlike sequence containers, associative containers do not preserve the relative positions of
the elements in them. Instead associative containers are built for speed, more specifically
element lookup speed.

As of the C++14 standard, there are now three
types of templates that can be used: class templates, function templates, and variable
templates.

The first potential drawback is that all templates must have their
entire implementation in the same file, usually the header.

Another drawback of templates is that
they are notorious for being hard to debug. Compilers tend to give cryptic errors when the
issue resides inside of the templated code.

The auto keyword has a helper keyword, decltype, which extracts the type from a
variable. So where auto is used to let the compiler infer what the variable type is, the
decltype is utilized to determine what a variable's type is.

Run-time type information
(RTTI), which is the concept of determining the type of a variable at runtime.

A somewhat more
ideal solution would be to have an EventHandler class that would handle the registration,
storage, and polymorphic functions for all events.

```
cl /c hello.cpp
lib /out:MyLib.lib hello.obj
cl main.cpp /link MyLib.lib

// using gcc on Linux/MacOS
gcc -c hello.cpp
ar rvs MyLib.a hello.o
g++ main.cpp MyLib.a -o main
```

Dynamic or shared libraries are libraries that have their code implementations linked at
runtime.

For dynamic or shared libraries, we have to make a few modifications and follow slightly different steps for compilation and linking. To begin with, we will have to change our library file to let the compiler know that we would like to share certain parts with other programs. We do this, on the Microsoft platform, with `__declspec` or declaration specification. Passing the `dllexport` parameter to `__declspec` lets the compiler know that this function or even classes should be exported as part of the dynamic linked library. On the OS X platform, we also use a type of declaration to let the compiler know that the classes or functions are to be exported. Here we use `__attribute__((visibility("default")))` in place of `__declspec`

For creating dynamic link library on Windows

```
cl /LD /FeMyDynamicLib.dll hello.cpp
```

`/LD` - Create dynamically linked library

The `.lib` of a dynamic library acts as a pointer to the actual implementation in the `.dll` file

In **Linker** select **Input**. At the top of the dialog on the **Additional Dependencies** property, click on the drop down and select **Edit**. we specify the libraries we wish to include at compile time. We include `.lib` file regardless of whether it is a dynamic library or static library.

Macros:
`$(SolutionDir)` This is the top solution directory
`$(SourceDir)` This is the directory of the source for the project
`$(Platform)` This is the platform that is selected (Win32, x64, ARM)
`$(Configuration)` This is the configuration that is selected (Debug/Release)

* OpenGL (https://www.opengl.org/): The **Open Graphics Library (OGL)** is an open cross-language, cross-platform application programming interface, or API, used for rendering 2D and 3D graphics. The API provides low-level access to the **Graphics Processing Unit (GPU)**.
SDL (https://www.libsdl.org/): The **Simple DirectMedia Layer (SDL)** is a cross-platform software development library designed to deliver a low-level hardware abstraction layer to multimedia hardware components. While it does provide its own mechanism for rendering, SDL can use **OGL** to provide full 3D rendering support.

An OGL context can be thought of as a set
of states that describes all the details related to the rendering of the application. The OGL
context must be set before any drawing can be done.

FFmpeg implements almost all the common data encapsulation formats, multimedia transmission protocol and audio and video codecs.

FFmpeg is functionally divided into several modules:
	* **libutils** - core tools
	* **libavformat** - media formats
	* **libavcodec** - codecs
	* **libavdevice** - devices
	* **libavfilter**, **libswscale**, **libpostproc** - post-processing

