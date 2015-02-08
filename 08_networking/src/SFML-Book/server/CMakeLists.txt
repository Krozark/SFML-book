set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/server)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(INCROOT_COMMON ${INCROOT}/../common)
set(SRCROOT_COMMON ${SRCROOT}/../common)


#FILES
set(FILES_HEADER
    ${INCROOT}/Client.hpp
    ${INCROOT}/Server.hpp

    ${INCROOT}/Game.hpp
    ${INCROOT}/Team.hpp

    ${INCROOT_COMMON}/Packet.hpp    
    ${INCROOT_COMMON}/FuncIds.hpp    
)

set(FILES_SRC
    ${SRCROOT}/Client.cpp
    ${SRCROOT}/Server.cpp

    ${SRCROOT}/Game.cpp
    ${SRCROOT}/Team.cpp

    ${SRCROOT_COMMON}/Packet.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-server ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-server ${LIBS})
