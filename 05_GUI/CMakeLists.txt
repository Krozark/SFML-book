set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

set(LIBS ${LIBS} Box2D sfgui)
# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(CHAPTER_NAME 05_GUI)

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

    #gui
    ${INCROOT}/gui/Button.hpp
    ${INCROOT}/gui/Container.hpp
    ${INCROOT}/gui/Frame.hpp
    ${INCROOT}/gui/Gui.hpp
    ${INCROOT}/gui/Label.hpp
    ${INCROOT}/gui/Layout.hpp
    ${INCROOT}/gui/TextButton.hpp
    ${INCROOT}/gui/VLayout.hpp
    ${INCROOT}/gui/Widget.hpp
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

    #gui
    ${SRCROOT}/gui/Button.cpp
    ${SRCROOT}/gui/Container.cpp
    ${SRCROOT}/gui/Frame.cpp
    ${SRCROOT}/gui/Label.cpp
    ${SRCROOT}/gui/Layout.cpp
    ${SRCROOT}/gui/TextButton.cpp
    ${SRCROOT}/gui/VLayout.cpp
    ${SRCROOT}/gui/Widget.cpp

)


add_executable(${CHAPTER_NAME} ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME} ${LIBS})
