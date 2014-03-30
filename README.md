[![Build Status](https://travis-ci.org/stephenyao/flappy_bear.svg?branch=develop)](https://travis-ci.org/stephenyao/flappy_bear)

### to build:
	mkdir build
	cd build
	cmake ..
	make
need to compile SDL2 with OpenGL (libgl1-mesa-dev for example on linux)

### to execute:
	cd build
	./flappy_bear

### equation of motion:
	s = s0 + v0*t - (g*t^2)/2
	v = v0 - g*t
	
