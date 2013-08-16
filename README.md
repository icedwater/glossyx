glossyx
=======

GL experiments using OSS software

20130814, 1500: This began from an attempt to follow a VS2010 workshop on Linux.

Install
=======
Necessary packages on Ubuntu 12.04 (with help from http://opengl-tutorial.org/):
 - g++
 - make
 - freeglut3-dev
 - libglewmx1.6-dev
 - libgl1-mesa-dev
 - libglu1-mesa-dev
 - libglm-dev
 - libxrandr-dev
 - libxext-dev

Install these packages using `sudo apt-get install <list-of-packages>`.

Eventually, this should be packaged into a DEB, possibly also an RPM, to make
installing easier.

Notes
=====
  - Make sure that `#include` calls have `GL` in uppercase. It matters for 
  Linux, not for Windows, so it's fine to do this in cross-platform code.
  - Compile argument should include `-lglut -lGL -lGLEW` for libraries.
  - I had to add links `ln -s` to a bunch of `win*.h` to compile `main.cpp`,
  but linking is still somehow lost. Where do I "build freeGLUT"?
  - Using `gcc` for `triangle.c` works fine.
  - Using `g++` for `sample.cpp` works fine.
