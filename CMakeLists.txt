cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# project name
project (SFML-Book)

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

set(DEFINES "")

find_library(LIB_SFML_SYSTEM sfml-system)
find_library(LIB_SFML_GRAPHICS sfml-graphics)
find_library(LIB_SFML_WINDOW sfml-window)
find_library(LIB_SFML_AUDIO sfml-audio)
set(LIBS ${LIB_SFML_SYSTEM} ${LIB_SFML_GRAPHICS} ${LIB_SFML_WINDOW} ${LIB_SFML_AUDIO})

set(WARNING "-Wall")
set(FLAGS "-g -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")


# add the subdirectories
add_subdirectory(01_Introduction)
add_subdirectory(02_Game_Archi)
add_subdirectory(03_Simple_2D_game)
#build exemples

