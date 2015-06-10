Symmetry Engine
===============

A library to drive complex light source ('pixel') based effects and interactions with LEDs and beyond.

Setup
-----

1. clone the library `git clone git@github.com:SymmetryLabs/electrify.git`
2. `cd electrify/engine`
3. `mkdir build; cd build`
4. `cmake ..`
5. `make` (add `-j 5` for multicore speed)

This will place [libSymmetryEngine.dylib shared library](http://en.wikipedia.org/wiki/Dynamic_loading) in the **lib** folder

Notes
-----
* [include](https://github.com/SymmetryLabs/electrify/tree/master/engine/include) has the header files for code to use the library
* see the notes in https://github.com/SymmetryLabs/electrify/blob/master/testapp/build.sh re env flags for using the shared library (more details for linux [here](http://www.cprogramming.com/tutorial/shared-libraries-linux-gcc.html) but osx uses different env vars (DYLD vs LD_LIBRARY_PATH ))

Frameworks
-----
* Testing: [catch](https://github.com/philsquared/Catch)
* Documentation: [doxygen](http://www.stack.nl/~dimitri/doxygen/)
* JSON: [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
