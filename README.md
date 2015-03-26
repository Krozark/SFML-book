SFML-book
=========

The code for the SFML book I write

Requirements
============

You need to have a valid clone of the SFML 2.2 or newer library (https://github.com/LaurentGomila/SFML/releases/tag/2.2) and need to build it.

Installation
============

* Clone this repo recursivly to get dependencies

     git clone --recursive https://github.com/Krozark/SFML-book.git
	
* Once it's done, use Cmake to build the project.
	
	cd path/to/SFML-Book
	mkdir build
	cd build
	cmake-gui ..
	
* You will need to set the variable
 * GLEW_INCLUDE_DIR to path/to/SFML/extlibs/headers
 * GLEW_LIBRARY to path/to/SFML/extlibs/libs-[compiler]/x[32/64]/libglew32.a depending on your system
* press "configure" and "generate"
* your file is now generated in the path/to/SFML-Book/build/ directory. You can use it to build the entire book projects.
* notice that for windows user, you will have to copy the dll of the externals libraries to your system path
 * lib
	 



Chapter 1: SFML Bases
----------


<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter1.png" alt="Chapter 1" height="250px">

Chapter 2: Create a player and game loop
----------

<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter2.png" alt="Chapter 2" height="250px">

Chapter 3: Create tow games : Asteroid and Teris clone
--------------------------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter3a.png" alt="Chapter 3" height="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter3b.png" alt="Chapter 3" height="350px">

Chapter 4: Play with physics
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter4.png" alt="Chapter 4" height="450px">

Chapter 5: Add a GUI
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter5a.png" alt="Chapter 5" height="250px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter5b.png" alt="Chapter 5" height="250px">

Chapter 6: Multithreading
----------
no graphical changes

Chapter 7: Create a Hybrid RTS/tower defence from sratch
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter7.png" alt="Chapter 7" height="450px">

Chapter 8: Play with networking, and tur to a multiplayer our game
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter8a.png" alt="Chapter 8" height="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter8b.png" alt="Chapter 8" height="450px">
