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


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)


# add the subdirectories
add_subdirectory(01_Introduction)
add_subdirectory(02_Game_Archi)
add_subdirectory(03_Simple_2D_game)
add_subdirectory(04_Physics)
add_subdirectory(05_GUI)
add_subdirectory(06_Multithreading)
#build exemples

