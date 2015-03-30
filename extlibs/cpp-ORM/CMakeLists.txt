cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

# project name
set(PROJECT_NAME ORM)
project(${PROJECT_NAME})

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 4)
set(VERSION_PATCH 1)


# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set_option(ORM_BUILD_SUPPORT_SQLITE3 TRUE BOOL "TRUE to build support for sqlite3 backends, FALSE to ignore them")
set_option(ORM_BUILD_SUPPORT_MYSQL FALSE BOOL "TRUE to build support for Mysql backends, FALSE to ignore them")

set_option(ORM_USE_CACHE TRUE BOOL "TRUE to buid a cache for database query, FALSE to ignore it")

set_option(ORM_BUILD_EXAMPLES FALSE BOOL "TRUE to build the examples, FALSE to ignore them")
set_option(ORM_BUILD_DOC FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it")


if(ORM_BUILD_SUPPORT_SQLITE3)
	if(UNIX)
		find_library(LIB_PTHREAD pthread)
		set(LIBS ${LIBS} ${LIB_PTHREAD})
	endif()
	add_definitions(-DSQLITE_OMIT_LOAD_EXTENSION)
endif()

if(ORM_BUILD_SUPPORT_MYSQL)
	find_library(LIB_MYSQL mysqlcppconn)
	set(LIBS ${LIBS} ${LIB_MYSQL})
endif()


if(ORM_USE_CACHE)
    add_definitions(-DORM_USE_CACHE)
endif()


set(WARNING "-Wall")
set(FLAGS "-o3 -DORM_USE_CACHE")
set(CMAKE_CXX_FLAGS "${WARNING} ${FLAGS} -std=c++11")
set(CMAKE_C_FLAGS "${WARNING} ${FLAGS}")

# add the subdirectories
add_subdirectory(src/ORM)
#build exemples
if(ORM_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(ORM_BUILD_DOC)
    add_subdirectory(doc)
endif()

