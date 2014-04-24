[![Build Status](https://travis-ci.org/stephenyao/flappy_bear.svg?branch=develop)](https://travis-ci.org/stephenyao/flappy_bear)

* see install-environment-ubuntu.sh for the list of dependencies
* note that SDL2 need to be compiled with OpenGL (libgl1-mesa-dev for example on linux)
* libboost is used in this project for testing
* for release build, use "cmake -DCMAKE_BUILD_TYPE=Release ..", default cmake is debug build (configured in CMakeLists.txt)
* to show make commands use "make VERBOSE=1"

### to build:
	mkdir build
	cd build
	cmake ..
	make

### to execute:
	./flappy_bear

### to test:
	./ut_flappy_bear

### equation of motion:
	s = s0 + v0*t - (a*t^2)/2
	v = v0 - g*t


