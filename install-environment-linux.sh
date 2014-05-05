#!/bin/bash

sdl='SDL2-2.0.3'
sdlimage='SDL2_image-2.0.0'
sdlttf='SDL2_ttf-2.0.12'

if [ $1 == 'apt' ]; then
	sudo apt-get update -qq
	sudo apt-get install -qq cmake
	sudo apt-get install -qq freetype*
	sudo apt-get install -qq libgl1-mesa-dev
	sudo apt-get install -qq libboost-dev libboost-test-dev

elif [ $1 == 'zypper' ]; then
	sudo zypper in --type pattern devel_C_C++ devel_basics
	sudo zypper in cmake freetype freetype-devel boost-devel libboost_test1_53_0 Mesa-libGL-devel

else
	echo "invalid input"
	exit 1

fi

wget "https://www.libsdl.org/projects/SDL_ttf/release/${sdlttf}.tar.gz"
wget "https://www.libsdl.org/projects/SDL_image/release/${sdlimage}.tar.gz"
wget "https://www.libsdl.org/release/${sdl}.tar.gz"

for f in ${sdl} ${sdlimage} ${sdlttf}; do
	tar xvzf $f.tar.gz
	cd $f
	./configure && make && sudo make install
	rm -rf $f
	cd -
done

export BOOST_ROOT=/usr/lib/

