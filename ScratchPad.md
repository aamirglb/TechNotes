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
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
Tip-xx: 
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

* Object-Oriented Software Construction [Mey97],

* the term "orthogonality" has come to signify a kind of independence or decoupling. Two or more things are orthogonal
if changes in one do not affect any of the others

* helicopters have four basic controls.
1) The _cyclic_ is the stick you hold in your right hand. Move it, and the helicopter moves in the corresponding direction.
2) Your left hand holds the _collective_ pitch lever. Pull up on this and you increase the pitch on all the blades, generating lift.
3) At the end of the pitch lever is the _throttle_.
4) Finally you have two _foot pedals_, which vary the amount of tail rotor thrust and so help turn the helicopter.

Decorator Pattern: adding functionality to things without changing them.

your code is easier to understand and maintain if you explicitly pass any required context into your modules.

In object-oriented applications, context is often passed as parameters to objects' constructors. In other code, you can create
structures containing the context and pass around references to them.

C++
===
* `std::enable_if_t<condition, type>` evaluates to type if condition is true. Otherwise, the std::enable_if_t expression does not evaluate to
anything.

* When the compiler sees different template functions with the same name and has to choose one of them, an important principle comes into play: **SFINAE**, which stands for _Substitution Failure is not an Error_. In this case, this means that the compiler does not
error out if the return value of one of those functions cannot be deduced from an erroneous template expression (which std::enable_if is, in case its condition evaluates to false).  It will simply look further and try the other function implementation. That is the trick; that is
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
