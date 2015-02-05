set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/server)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

#FILES
set(FILES_HEADER
    ${INCROOT}/Client.hpp
    ${INCROOT}/Server.hpp
)

set(FILES_SRC
    ${SRCROOT}/Client.cpp
    ${SRCROOT}/Server.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-server ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-server ${LIBS})
