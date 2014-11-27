set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 04_Gravitris)

#FILES
set(FILES_HEADER
    ${INCROOT}/Action.hpp
    ${INCROOT}/ActionMap.hpp
    ${INCROOT}/ActionMap.tpl
    ${INCROOT}/ActionTarget.hpp
    ${INCROOT}/ActionTarget.tpl
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/converter.hpp
    ${INCROOT}/DebugDraw.hpp
    ${INCROOT}/Game.hpp
    ${INCROOT}/Piece.hpp
    ${INCROOT}/random.hpp
    ${INCROOT}/ResourceManager.hpp
    ${INCROOT}/ResourceManager.tpl
    ${INCROOT}/Stats.hpp
    ${INCROOT}/World.hpp
)

set(FILES_SRC
    ${SRCROOT}/Action.cpp
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/DebugDraw.cpp
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Piece.cpp
    ${SRCROOT}/Stats.cpp
    ${SRCROOT}/World.cpp

    ${SRCROOT}/main.cpp

)


add_executable(${CHAPTER_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME} ${LIBS})
