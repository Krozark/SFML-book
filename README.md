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
 * SFML-book\extlibs\SFML-utils\extlibs\cpp-utils\examples\*.dll
 * SFML-book\extlibs\SFML-utils\examples\*.dll

	 



Chapter 1:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter1.png" alt="Chapter 1" height="250px">

Chapter 2:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter2.png" alt="Chapter 2" height="250px">

Chapter 3:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter3a.png" alt="Chapter 3" height="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter3b.png" alt="Chapter 3" height="350px">

Chapter 4:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter4.png" alt="Chapter 4" height="450px">

Chapter 5:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter5a.png" alt="Chapter 5" height="250px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter5b.png" alt="Chapter 5" height="250px">

Chapter 6:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter6.png" alt="Chapter 6" height="250px">

Chapter 7:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter7.png" alt="Chapter 7" height="450px">

Chapter 8:
----------
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter8a.png" alt="Chapter 8" height="350px">
<img src="https://raw.githubusercontent.com/Krozark/SFML-book/master/screen/Chapter8b.png" alt="Chapter 8" height="450px">
