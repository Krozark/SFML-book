set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

set(LIBS ${LIBS} SFML-utils-core SFML-utils-es SFML-utils-gui SFML-utils-map utils)
# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 07_2D_iso_game)

#FILES
set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Game.hpp
    ${INCROOT}/Level.hpp
    ${INCROOT}/Team.hpp
    ${INCROOT}/TeamGui.hpp

    ${INCROOT}/Entity.hpp
    ${INCROOT}/Component.hpp
    ${INCROOT}/System.hpp

    ${INCROOT}/Helpers.hpp
    ${INCROOT}/random.hpp

)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Level.cpp
    ${SRCROOT}/Team.cpp
    ${SRCROOT}/TeamGui.cpp

    ${SRCROOT}/Entity.cpp
    ${SRCROOT}/Component.cpp
    ${SRCROOT}/System.cpp

    ${SRCROOT}/Helpers.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME} ${LIBS})
