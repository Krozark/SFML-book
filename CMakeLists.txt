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

set_option(BOOK_BUILD_CHAPTER_1 TRUE BOOL "Build chapter 1")
set_option(BOOK_BUILD_CHAPTER_2 TRUE BOOL "Build chapter 2")
set_option(BOOK_BUILD_CHAPTER_3 TRUE BOOL "Build chapter 3")
set_option(BOOK_BUILD_CHAPTER_4 TRUE BOOL "Build chapter 4. Require Box2d")
set_option(BOOK_BUILD_CHAPTER_5 TRUE BOOL "Build chapter 5. Require Box2d and SFGUI")
set_option(BOOK_BUILD_CHAPTER_6 TRUE BOOL "Build chapter 6. Require Box2d ans SFGUI")
set_option(BOOK_BUILD_CHAPTER_7 TRUE BOOL "Build chapter 7. Required SFML-utils")
set_option(BOOK_BUILD_CHAPTER_8 TRUE BOOL "Build chapter 8. Required SFML-utils")

set(WARNING "-Wall")
set(FLAGS "-g -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)


# add the subdirectories
if(BOOK_BUILD_CHAPTER_1)
    add_subdirectory(01_Introduction)
endif()

if(BOOK_BUILD_CHAPTER_2)
    add_subdirectory(02_Game_Archi)
endif()

if(BOOK_BUILD_CHAPTER_3)
    add_subdirectory(03_Simple_2D_game)
endif()

if(BOOK_BUILD_CHAPTER_4)
    add_subdirectory(04_Physics)
endif()

if(BOOK_BUILD_CHAPTER_5)
    add_subdirectory(05_GUI)
endif()

if(BOOK_BUILD_CHAPTER_6)
    add_subdirectory(06_Multithreading)
endif()

if(BOOK_BUILD_CHAPTER_7)
    add_subdirectory(07_2D_iso_game)
endif()

if(BOOK_BUILD_CHAPTER_8)
    add_subdirectory(08_networking)
endif()

