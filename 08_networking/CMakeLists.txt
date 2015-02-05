find_library(LIB_SFUTILS_CORE SFML-utils-core)
find_library(LIB_SFUTILS_ES SFML-utils-es)
find_library(LIB_SFUTILS_GUI SFML-utils-gui)
find_library(LIB_SFUTILS_MAP SFML-utils-map)
find_library(LIB_UTILS utils)
set(LIBS ${LIBS} ${LIB_SFUTILS_CORE} ${LIB_SFUTILS_ES} ${LIB_SFUTILS_GUI} ${LIB_SFUTILS_MAP} ${LIB_UTILS})

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 08_networking)

add_subdirectory(src/SFML-Book/common)
add_subdirectory(src/SFML-Book/client)
add_subdirectory(src/SFML-Book/server)

