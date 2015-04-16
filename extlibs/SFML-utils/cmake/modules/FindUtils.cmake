# This script locates the UTILS library.
#
# USAGE
# find_package( UTILS )
#
# If UTILS is not installed in a standard path, you can use
# UTILS_ROOT CMake (or environment) variables to tell CMake where to look for
# UTILS.
#
#
# OUTPUT
#
# This script defines the following variables:
#   - UTILS_LIBRARY:         the path to the library to link to
#   - UTILS_FOUND:           true if the UTILS library is found
#   - UTILS_INCLUDE_DIR:     the path where UTILS headers are located
#
#
# EXAMPLE
#
# find_package( UTILS REQUIRED )
# include_directories( ${UTILS_INCLUDE_DIR} )
# add_executable( myapp ... )
# target_link_libraries( myapp ${UTILS_LIBRARY} ... )

set( UTILS_FOUND false )

find_path(
	UTILS_INCLUDE_DIR
	UTILS/sys.hpp
	PATH_SUFFIXES
		include
	PATHS
		/usr
		/usr/local
		${UTILSDIR}
		${UTILS_ROOT}
		$ENV{UTILS_ROOT}
		$ENV{UTILSDIR}
)

find_library(
	UTILS_LIBRARY
	utils${SFGUI_SUFFIX}
	PATH_SUFFIXES
		lib
		lib64
	PATHS
		/usr
		/usr/local
		${UTILSDIR}
		${UTILS_ROOT}
		$ENV{UTILS_ROOT}
		$ENV{UTILSDIR}
)

if( NOT UTILS_INCLUDE_DIR OR NOT UTILS_LIBRARY )
	message( FATAL_ERROR "cpp-utils not found. Set UTILS_ROOT to the installation root directory (containing inculde/ and lib/)" )
else()
	message( STATUS "cpp-utils found: ${UTILS_INCLUDE_DIR}" )
endif()
