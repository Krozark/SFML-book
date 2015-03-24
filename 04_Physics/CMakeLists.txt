#INCLUDE_DIRECTORIES(${Box2D_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/extlibs)

find_package(Box2D)
set(LIBS ${LIBS} ${BOX2D_LIBRARIES})

add_subdirectory(Basic)
add_subdirectory(Gravitris)
