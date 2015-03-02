set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 02_Game_Archi)

#FILES
set(FILES_HEADER
    ${INCROOT}/Action.hpp
    ${INCROOT}/ActionTarget.hpp
    ${INCROOT}/ActionTarget.tpl
    ${INCROOT}/ActionMap.hpp
    ${INCROOT}/ActionMap.tpl
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Game.hpp
    ${INCROOT}/Player.hpp
    ${INCROOT}/Player.tpl
    ${INCROOT}/ResourceManager.hpp
    ${INCROOT}/ResourceManager.tpl
)

set(FILES_SRC
    ${SRCROOT}/Action.cpp
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Player.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME} ${LIBS})
