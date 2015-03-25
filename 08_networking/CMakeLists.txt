set(LIBS ${LIBS} SFML-utils-core SFML-utils-es SFML-utils-gui SFML-utils-map utils)

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 08_networking)

add_subdirectory(src/SFML-Book/common)
add_subdirectory(src/SFML-Book/client)
add_subdirectory(src/SFML-Book/server)

