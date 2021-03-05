# Open CV Notes 
## Misc Notes

* JavaScript was introduced in 1995 as a way to add programs to web pages in the Netscape Navigator browser. applications with which you can interact directly without doing a page reload for every action. 

* OpenCV and the Leptonica Image Processing Library
* Jenkins to continuously build the project
  
* Peer-to-peer distribution based on the Chord algorithm

* **CUDA** is a parallel computing platform and programming model that makes using a **_GPU for general purpose computing simple and elegant_**. The developer still programs in the familiar C, C++, Fortran, or an ever expanding list of supported languages, and incorporates extensions of these languages in the form of a few basic keywords.

* **ANGLE (*Almost Native Graphics Layer Engine*)**  
 Translate OpenGL ES (Open Graphics Library for Embedded Systems) calls to one of the hardware supported APIs for the platform. OpenGL ES 2.0 & 3.0 to Desktop OpenGL, OpenGL ES, Direct3D 9, Direct3D 11, Vulkan(underway)

* **Mesa Library**  
 Mesa, also called Mesa3D and The Mesa 3D Graphics Library, is an open source software implementation of OpenGL, Vulkan, and other graphics specifications. *Mesa implements a cross-language, cross-platform, vendor-neutral standard API for translating these specifications to vendor-specific graphics hardware drivers.*

* **FFmpeg**  
 FFmpeg is a complete, cross platform command line tool capable of recording, converting and streaming digital audio and video in various formats.

  FFmpeg devs had to keep a default setting for the audio and video bitrate, they settled on a 64kbps audio(radio quality) and 200 kbps for video, a bad video quality.

  Movie files ares called a **container**, and the type of container determines where the information in the file goes. Examples of containers are **AVI** and **Quicktime**. Next, you have a bunch of streams; for example, you usually have an **audio stream** and a **video stream**. The data elements in a stream are called **frames**. Each stream is encoded by a different kind of codec. The codec defines how the actual data is _COded_ and _DECoded_. Examples of codecs are **DivX** and **MP3**.

  **YUV overlay**. YUV (technically not YUV but YCbCr)  
  Generally speaking, YUV is an analog format and YCbCr is a digital format. "YUV" is a way of storing raw image data like RGB. Roughly speaking, Y is the brightness (or "luma") component, and U and V are the color components.

  **PTS and DTS**  
  Fortunately, both the audio and video streams have the information about how fast and when you are supposed to play them inside of them. Audio streams have a **sample rate**, and the video streams have a **frames per second** value. However, if we simply synced the video by just counting frames and multiplying by frame rate, there is a chance that it will go out of sync with the audio. Instead, packets from the stream might have what is called a **decoding time stamp (DTS)** and a **presentation time stamp (PTS)**. To understand these two values, you need to know about the way movies are stored.  
  
  Some formats, like **MPEG**, use what they call **"B" frames** (B stands for "bidirectional"). The two other kinds of frames are called **"I" frames** and **"P" frames** ("I" for "intra" and "P" for "predicted"). I frames contain a full image. P frames depend upon previous I and P frames and are like diffs or deltas. B frames are the same as P frames, but depend upon information found in frames that are displayed both before and after them!

* **Simple DirectMedia Layer (SDL)**  
 SDL is a cross-platform development library designed to provide low level access to audio, keyboard, mouse, joystick, and graphics hardware via OpenGL and Direct3D. It is used by video playback software, emulators, and popular games

### Using Open CV with MinGW & MS VS

* OpenCV 3.0 prebuilt binaries provide libraries only for x64 (64-bit platform), to use x86 (32-bit platform), we have to recompile the Open CV source code using CMake and MinGW/MSVC++ compiler.

* Microsoft Visual Studio 2017 is a 32-bit compiler, but it can be use to generate executables for both x86 & x64 platform. To do this select Platfrom as x86/x64 from Project Configuration settings.

* For debug version of executable, debug version of the library should be selected and for release version of executable, release version of library should be selected. 

## Open CV

* OpenCV 3.x sits on top of a hardware acceleration layer (HAL) so that implemented algorithms can run efficiently, seamlessly taking advantage of a variety of hardware platforms.

* The mathematics involve simple algebra and basic matrix algebra, and assume some familiarity with solution methods to **least-squares optimization problems** as well as some basic knowledge of **Gaussian distributions, Bayes law, and derivatives of simple functions**.

* OpenCV is an open source computer vision library, written in C and C++ and runs under Linux, Windows, and Mac OS X also providing interfaces for Python, Java, MATLAB, and other languages, including porting the library to Android and iOS for mobile applications.

* It is written in optimized C++ and can take advantage of multicore processors. For automatic optimization on Intel architectures, buy Intel’s **_Integrated Performance Primitives (IPP) libraries_**, which consist of low-level optimized routines in many different algorithmic areas. OpenCV automatically uses the appropriate IPP library at runtime if that library is installed.

* The OpenCV library contains over **_500_** functions that span many areas in vision, including
  * factory product inspection, 
  * medical imaging, 
  * security, 
  * user interface, 
  * camera calibration,
  * stereo vision, and 
  * robotics.

* Computer vision is the transformation of data from a still or video camera into either a decision or a new representation.

* `setx -m OPENCV_DIR D:\OpenCV\Build\x64\vc10`  
   Add `%OPENCV_DIR%\bin` to library path

* To build OpenCV libraries and demos on Linux, you’ll need  
  * **_GTK+ 2.x or higher_**, including headers. 
  * gcc and the essential development packages, 
  * _cmake_
  * _libtbb_ (Intel thread building blocks), and optionally
  * *zlib*,
  * *libpng*,
  * *libjpeg*,
  * *libtiff*, and
  * *libjasper* with development files
  * Python 2.6 or later with headers installed
  * _libavcodec_ and the other _libav_ libraries (including headers) from _ffmpeg_

### Open CV Modules

 > **1. core**  
   >The “core” is the section of the library that contains all of the basic object types
   > and their basic operations.

   > **2. imgproc**  
   >The image processing module contains basic transformations on images, including filters  and similar convolutional operators.

   > **3. highgui** (split to imgcodecs, videoio, and highgui in OpenCV 3.0)  
   >This module contains user interface functions that can be used to display images or take >simple user input. It can be thought of as a very lightweight window UI toolkit.

   > **4. video**  
   > The video library contains the functions you need to read and write video streams.

   > **5. calib3d**  
   > This module contains implementations of algorithms you will need to calibrate single 
   > cameras as well as stereo or multicamera arrays.

   > **6. features2d**  
   > This module contains algorithms for detecting, describing, and matching keypoint 
   > features.

   > **7. objdetect**  
   > This module contains algorithms for detecting specific objects, such as faces or pedestrians. > You can train the detectors to detect other objects as well.

   > **8. ml**  
   > The Machine Learning library is actually an entire library in itself, and contains a wide array of machine learning algorithms implemented in such a way as to work with the natural data structures of OpenCV.

   > **9. flann**  
   > FLANN stands for “Fast Library for Approximate Nearest Neighbors.” This library contains methods you will not likely use directly, but which are used by other functions in other modules for doing nearest neighbor searches in large data sets.

   > **10. gpu** _(split to multiple cuda* modules in OpenCV 3.0)_  
   > The GPU library contains implementations of most of the rest of the library functions optimized for operation on CUDA GPUs. There are also some functions that are implemented only for GPU operation. Some of these provide excellent results but require computational resources sufficiently high that implementation on non-GPU hardware would provide little utility.

   > **11. photo**  
   > This is a relatively new module that contains tools useful for computational photography.

   > **12. stitching**  
   > This entire module implements a sophisticated image stitching pipeline. This is new functionality in the library, but, like the photo module, it is an area where future growth is expected.

   > **13. nonfree** _(moved to opencv_contrib/xfeatures2d in OpenCV 3.0)_  
   > OpenCV contains some implementations of algorithms that are patented or otherwise burdened by usage restrictions (e.g., the SIFT algorithm). Those algorithms are segregated into their own module to indicate that you will need to do some kind of special work in order to use them in a commercial product.

   > **14. contrib** _(melted into a few opencv_contrib modules in OpenCV 3.0)_  
   > This module contains new things that have yet to be integrated into the whole of the library.

   > **15. legacy** _(disappeared in OpenCV 3.0)_  
   > This module contains old things that have yet to be banished from the library altogether.

   > **16. ocl** _(disappeared in OpenCV 3.0; replaced with T-API technology)_  
   > This is a newer module that could be considered analogous to the GPU module, except that it implements the Khronos OpenCL standard for open parallel programming. Though much less featured than the GPU module at this time, the ocl module aims to provide implementations that can run on any GPU or other Khronos-capable parallel device. (This is in contrast to the gpu module, which explicitly makes use of the NVidia CUDA toolkit and so will work only on NVidia GPU devices.)
  
* OpenCV provides utilities for reading from a wide array of image file types, as well as from video and cameras. These utilities are part of a toolkit called **HighGUI**.

* `cv::imread()` is a high-level routine that determines the file format to be loaded based on the filename; it also automatically allocates the memory needed for the image data structure.

* `cv::imread()` can read a wide variety of image formats, including `BMP, DIB, JPEG, JPE, PNG, PBM, PGM, PPM, SR, RAS, and TIFF`.

* `cv::Mat` structure is used to handle all kinds of images: single-channel, multichannel, integer-valued, floating-point-valued, and so on. With cv::Mat, images are automatically deallocated when they go out of scope

* `cv::namedWindow()`, opens a window on the screen that can contain and display an image.

* `cv::imshow()` display an image from a cv::Mat structure

* `cv::waitKey()` function asks the program to stop and wait for a keystroke. If the argument is set to 0 or to a negative number, the program will wait indefinitely for a key-press.

* `cv::destroyWindow()` will close the window and deallocate any associated memory usage.

* `cv::VideoCapture` object can open and close video files of as many types as *ffmpeg* supports.

* `cv::createTrackbar()` enables users to jump easily from one part of a video to another.

* `g_cap.set()` and `g_cap.get()` routines allow us to configure (or query, in the latter case) various properties of the `cv::VideoCapture` object.

* Many basic vision tasks involve the application of filters to a video stream. **_smoothing_** an image, which effectively reduces the information content of the image by convolving it with a Gaussian or other similar kernel function.
