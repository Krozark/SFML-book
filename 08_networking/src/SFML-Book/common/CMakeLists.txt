set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/common)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(INCROOT_SERVER ${INCROOT}/../server)
set(SRCROOT_SERVER ${SRCROOT}/../server)

#FILES
set(FILES_HEADER

    #${INCROOT}/Configuration.hpp
    #${INCROOT}/Game.hpp
    #${INCROOT}/Level.hpp
    #${INCROOT}/Team.hpp
    #${INCROOT}/TeamGui.hpp

    #${INCROOT}/Entity.hpp
    #${INCROOT}/Component.hpp
    #${INCROOT}/System.hpp

    #${INCROOT}/Helpers.hpp
    #${INCROOT}/random.hpp

    ${INCROOT}/Packet.hpp
    ${INCROOT}/Connection.hpp

    ${INCROOT_SERVER}/Game.hpp

)

set(FILES_SRC
    #${SRCROOT}/Configuration.cpp
    #${SRCROOT}/Game.cpp
    #${SRCROOT}/Level.cpp
    #${SRCROOT}/Team.cpp
    #${SRCROOT}/TeamGui.cpp

    #${SRCROOT}/Entity.cpp
    #${SRCROOT}/Component.cpp
    #${SRCROOT}/System.cpp

    #${SRCROOT}/Helpers.cpp

    ${SRCROOT}/Packet.cpp
    ${SRCROOT}/Connection.cpp

    ${SRCROOT_SERVER}/Game.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-common ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-common ${LIBS})
