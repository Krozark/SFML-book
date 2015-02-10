set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/client)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(INCROOT_COMMON ${INCROOT}/../common)
set(SRCROOT_COMMON ${SRCROOT}/../common)

#FILES
set(FILES_HEADER
    ${INCROOT}/Client.hpp

    ${INCROOT_COMMON}/Packet.hpp    
    ${INCROOT_COMMON}/FuncIds.hpp
    ${INCROOT_COMMON}/Connection.hpp
)

set(FILES_SRC
    ${SRCROOT}/Client.cpp

    ${SRCROOT_COMMON}/Packet.cpp
    ${SRCROOT_COMMON}/Connection.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-client ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-client ${LIBS})
