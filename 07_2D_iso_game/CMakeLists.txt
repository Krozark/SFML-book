set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

find_library(LIB_SFUTILS_CORE SFML-utils-core)
find_library(LIB_SFUTILS_ES SFML-utils-es)
find_library(LIB_SFUTILS_GUI SFML-utils-gui)
find_library(LIB_SFUTILS_MAP SFML-utils-map)
find_library(LIB_UTILS utils)
set(LIBS ${LIBS} ${LIB_SFUTILS_CORE} ${LIB_SFUTILS_ES} ${LIB_SFUTILS_GUI} ${LIB_SFUTILS_MAP} ${LIB_UTILS})

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 07_2D_iso_game)

#FILES
set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Entity.hpp
    ${INCROOT}/Game.hpp
    ${INCROOT}/Level.hpp
)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/Entity.cpp
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Level.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME} ${LIBS})
