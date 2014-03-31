[![Build Status](https://travis-ci.org/stephenyao/flappy_bear.svg?branch=develop)](https://travis-ci.org/stephenyao/flappy_bear)

### to build:
	mkdir build
	cd build
	cmake ..
	make
* need to compile SDL2 with OpenGL (libgl1-mesa-dev for example on linux)
* libboost is used in this project

### to execute:
	./flappy_bear

### to test:
	./ut_flappy_bear
* library used for testing is libboost-test-dev

### equation of motion:
	s = s0 + v0*t - (a*t^2)/2
	v = v0 - g*t
	
### class structure:
	            texture
	            /     \
	    collidable    background
	    /        \
	player    obstacles
