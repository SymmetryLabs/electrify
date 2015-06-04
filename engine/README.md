Symmetry Engine
===============

A library to drive complex light source ('pixel') based effects and interactions with LEDs and beyond.

Setup
-----
1. clone the library `git clone git@github.com:SymmetryLabs/electrify.git`
2. `cd electrify/engine`
3. run `make` (or (deprecated) run [build.sh](https://github.com/SymmetryLabs/electrifying-stunt/blob/master/engine/build.sh) ). Both will place the [libengine.so shared library](http://en.wikipedia.org/wiki/Dynamic_loading) in the **lib** folder

Notes
-----
* [include](https://github.com/SymmetryLabs/electrifying-stunt/tree/master/engine/include) has the header files for code to use the library
* see the notes in https://github.com/SymmetryLabs/electrifying-stunt/blob/master/testapp/build.sh re env flags for using the shared library (more details for linux [here](http://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html) but osx uses different env vars (DYLD vs LD_LIBRARY_PATH ))

Frameworks
-----
* Testing: [catch](https://github.com/philsquared/Catch)
* Documentation: [doxygen](http://www.stack.nl/~dimitri/doxygen/)
