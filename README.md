[![Build Status](https://travis-ci.org/stephenyao/flappy_bear.svg?branch=develop)](https://travis-ci.org/stephenyao/flappy_bear)

### to build:
* need to compile SDL2 with OpenGL (libgl1-mesa-dev for example on linux)
* libboost is used in this project
	mkdir build
	cd build
	cmake ..
	make

### to execute:
	./flappy_bear

### to test:
* library used for testing is libboost-test-dev
	./ut_flappy_bear

### equation of motion:
	s = s0 + v0*t - (a*t^2)/2
	v = v0 - g*t
	
