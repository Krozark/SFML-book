set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/client)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

#FILES
set(FILES_HEADER
    ${INCROOT}/Client.hpp
)

set(FILES_SRC
    ${SRCROOT}/Client.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-client ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-client ${LIBS})
