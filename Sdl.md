# Simple DirectMedia Layer (SDL)

* **Simple DirectMedia Layer (SDL)** is a cross-platform multimedia library created by
Sam Oscar Latinga. It provides low-level access to input (via mouse, keyboard, and
gamepads/joysticks), 3D hardware, and the 2D video frame buffer. SDL is written
in the C programming language, yet has native support for C++. The library also
has bindings for several other languages such as Pascal, Objective-C, Python, Ruby,
and Java; a full list of supported languages is available at 

* http://www.libsdl.org/languages.php

* Each platform has its own way of creating and displaying windows and graphics,
handling user input, and accessing any low-level hardware; each one with its own
intricacies and syntax. SDL provides a uniform way of accessing these platform-
specific features.

* SDL has separate extensions that can be used to add new capabilities to the library.
The reason these extensions are not included in the first place is to keep SDL as
lightweight as possible, with the extensions serving to add functionality only when
necessary.

![](images/sdl/sdl_extensions.png)

* Building SDL 2.0 on Windows also requires the latest DirectX SDK,

* **TortoiseHg**, a free and user-friendly mercurial application; it is available at tortoisehg.bitbucket.org.

```c
// initializes all of SDL's subsystems
SDL_Init(SDL_INIT_EVERYTHING)
```

* `SDL_CreateWindow` returns a pointer to a window matching the
passed parameters. The parameters are the window title, x position of the
window, y position of the window, width, height, and any required SDL_
flags.

* Event handling, file I/O, and threading subsystems are all initialized by default in
SDL. Other subsystems can be initialized using the following flags

![](images/sdl/sdl_init_flags.png)


![](images/sdl/sdl_render_flag.png)

![](images/sdl/sdl_win_flags.png)

* SDL can use two structures to draw to the screen. One is the `SDL_Surface` structure, which contains a collection of pixels and is rendered
using _software rendering processes (not the GPU)_. The other is `SDL_Texture`; this can be used for _hardware-accelerated rendering_.

* https://www.widgetworx.com/spritelib/

* `SpriteLib` is a collection of static and animated graphic objects available for free.

* The Open Sound System (OSS) is the original sound-programming interface for
Linux. Maintained by 4Front Technologies, OSS provides a consistent
kernel-based interface to sound hardware.

* Advanced Linux Sound Architecture (ALSA) is a community project that seeks
to surpass OSS in all areas. The ALSA team has created a complete set of
kernel-level sound card drivers, an easy-to-use programming interface, and a
facility for emulating OSS.

* The Enlightened Sound Daemon (ESD, also called EsounD) is a sound server
that allows multiple applications to share a single sound card. ESD-aware
applications send their sound streams to ESD, and ESD mixes them internally
into a single output stream.

* The Open Audio Library (OpenAL) is an environmental 3D audio library that
supports just about every major platform. It aims to provide an open
replacement for proprietary (and generally incompatible) 3D audio systems such
as EAX and A3D.

* OpenAL can add realism to a game by simulating attenuation
(degradation of sound over distance), the Doppler effect (change in frequency as
a result of motion), and material densities.

* `libpng` and `libjpeg`: These two libraries allow you to load **Portable Network Graphic (.png)** and **JPEG (.jpg)** images, respectively. 

* PNG is an excellent general-purpose image format that compresses images without loss in detail. It is based on a completely open specification, and it is widely supported by image manipulation programs.

* JPEG is an older, “lossy” image format that does a good job with landscapes
and other natural scenes but produces noticeably lousy results with precise
images such as line art. JPEG is also an open standard.