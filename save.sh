#!/bin/bash

echo "Now I\'l save your main.cpp in the current directory"
echo "Are you ready?"

read answer

if [ $answer != "yes" ] ;then
	echo "Ok, goodbye!"
	exit
fi

echo "Input directory"

read directory

if [ $directory != "." ] ;then
	mkdir ../SavingCpp/${directory}
	
	cp -r src ../SavingCpp/${directory}/src
	cp -r test ../SavingCpp/${directory}/test
	cp -r cmake ../SavingCpp/${directory}/cmake
        cp -r CMakeLists.txt ../SavingCpp/${directory}/CMakeLists.txt
	cp -r build ../SavingCpp/${directory}/build 	
fi

bash setup.sh
