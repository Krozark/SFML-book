cmake_minimum_required (VERSION 2.8)

# define a macro that helps defining an option
macro(set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()

function(Compile arg shared_libs static_libs)
    add_library(${arg} SHARED ${FILES_SRC} ${FILES_HEADER})
    SET_TARGET_PROPERTIES(${arg}
        PROPERTIES
        OUTPUT_NAME ${arg}
        CLEAN_DIRECT_OUTPUT 1
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
        )
    target_link_libraries(${arg} ${LIBS} ${shared_libs})
    INSTALL(TARGETS ${arg}
        DESTINATION lib
    )

    add_library(${arg}-static STATIC ${FILES_HEADER} ${FILES_SRC})
    SET_TARGET_PROPERTIES(${arg}-static
        PROPERTIES
        OUTPUT_NAME ${arg}
        CLEAN_DIRECT_OUTPUT 1
        VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
        SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
        )
    target_link_libraries(${arg}-static ${LIBS} ${static_libs})
    INSTALL(TARGETS ${arg}-static
    DESTINATION lib
    )
endfunction()

# project name
set(PROJECT_NAME utils)
project (${PROJECT_NAME})

# setup version numbers
set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 8)


# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/src)

# add an option for choosing the build type (shared or static)
#set_option(BUILD_SHARED_LIBS FALSE BOOL "TRUE to build as shared libraries, FALSE to build it as static libraries")

#add an option for building the examples
set_option(UTILS_BUILD_EXAMPLES FALSE BOOL "TRUE to build the examples, FALSE to ignore them")

# add an option for building the API documentation
set_option(UTILS_BUILD_DOC FALSE BOOL "TRUE to generate the API documentation, FALSE to ignore it")

# add an option for building the API documentation
set_option(UTILS_BUILD_JSON TRUE BOOL "TRUE to generate json parser, FALSE to ignore it")

set_option(UTILS_BUILD_PARSER FALSE BOOL "TRUE to use flex/bison to generate the parsers, FALSE to ignore it")

set(LIBS "")

if(${WIN32})
    find_library(PTHREAD_LIB "winpthread-1")
    find_library(KERNEL_LIBS kernel32)#dlopen
    set(LIBS ${PTHREAD_LIB} ${KERNEL_LIB})
else()
    find_library(PTHREAD_LIB pthread)
    find_library(DL_LIB dl)#dlopen
    set(LIBS ${PTHREAD_LIB} ${DL_LIB})
endif()

#set(includepath "-I${CMAKE_CURRENT_SOURCE_DIR}/include")
set(DEFINES "")
set(WARNING "-Wall")
set(FLAGS "-g -std=c++0x")
set(CMAKE_CXX_FLAGS "${DEFINES} ${WARNING} ${FLAGS}")

# add the subdirectories
add_subdirectory(src/${PROJECT_NAME})
if(UTILS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
#build doc
if(UTILS_BUILD_DOC)
    add_subdirectory(doc)
endif()

