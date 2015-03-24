include_directories(${CMAKE_SOURCE_DIR}/extlibs)

set(LIBS ${LIBS} Box2D)

add_subdirectory(Basic)
add_subdirectory(Gravitris)
