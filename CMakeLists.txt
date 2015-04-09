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


#find SFML
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/../SFML PATH "The SFML root installation")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/SFML PATH "The SFML root installation")
else()
    set_option(SFML_ROOT ${CMAKE_INSTALL_PREFIX}/SFML PATH "The SFML root installation")
endif()


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules;${CMAKE_SOURCE_DIR}")

find_package(SFML 2 COMPONENTS system graphics window audio network)
if(NOT SFML_FOUND)
	message(FATAL_ERROR "SFML Modules not find. Please set the SFML_ROOT variable to your SFML root installation directory and retry")
endif()

#add SFML
include_directories(${SFML_INCLUDE_DIR})
set(LIBS ${SFML_LIBRARIES})

#choose chapters
set_option(BOOK_BUILD_CHAPTER_1 TRUE BOOL "Build chapter 1")
set_option(BOOK_BUILD_CHAPTER_2 TRUE BOOL "Build chapter 2")
set_option(BOOK_BUILD_CHAPTER_3 TRUE BOOL "Build chapter 3")
set_option(BOOK_BUILD_CHAPTER_4 TRUE BOOL "Build chapter 4. Require Box2D")
set_option(BOOK_BUILD_CHAPTER_5 TRUE BOOL "Build chapter 5. Require Box2D and SFGUI")
set_option(BOOK_BUILD_CHAPTER_6 TRUE BOOL "Build chapter 6. Require Box2D and SFGUI")
set_option(BOOK_BUILD_CHAPTER_7 TRUE BOOL "Build chapter 7. Required SFML-utils")
set_option(BOOK_BUILD_CHAPTER_8 TRUE BOOL "Build chapter 8. Required SFML-utils")

#custom compiler flags
add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DORM_USE_CACHE)

set(WARNING "-Wall")
set(FLAGS "-o3 -std=c++11")
set(CMAKE_CXX_FLAGS "${WARNING} ${FLAGS}")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1 )

#set output dirs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(LIB_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)


#extlibs
include_directories(${CMAKE_SOURCE_DIR}/extlibs)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/SFGUI/include)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/cpp-utils/include)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/SFML-utils/include)
include_directories(${CMAKE_SOURCE_DIR}/extlibs/cpp-ORM/include)

add_subdirectory(extlibs/Box2D)
add_subdirectory(extlibs/SFGUI)
add_subdirectory(extlibs/cpp-utils)
add_subdirectory(extlibs/SFML-utils)
add_subdirectory(extlibs/cpp-ORM)


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

#Box2D
if(BOOK_BUILD_CHAPTER_4)
    add_subdirectory(04_Physics)
endif()

#Box2D, SFGUI
if(BOOK_BUILD_CHAPTER_5)
    add_subdirectory(05_GUI)
endif()

#Box2D, SFGUI
if(BOOK_BUILD_CHAPTER_6)
    add_subdirectory(06_Multithreading)
endif()

#SFML-utils
if(BOOK_BUILD_CHAPTER_7)
    add_subdirectory(07_2D_iso_game)
endif()

#SFML-utils
if(BOOK_BUILD_CHAPTER_8)
    add_subdirectory(08_Multiplayer)
endif()

