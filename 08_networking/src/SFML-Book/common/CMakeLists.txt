set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/${CMAKE_PROJECT_NAME}/common)
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR})

#FILES
set(FILES_HEADER

    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Connection.hpp
    ${INCROOT}/FuncIds.hpp
    ${INCROOT}/Packet.hpp
    ${INCROOT}/random.hpp
    ${INCROOT}/std_hash.hpp


)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/Packet.cpp
    ${SRCROOT}/Connection.cpp

    ${SRCROOT}/main.cpp
)


add_executable(${CHAPTER_NAME}-common ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CHAPTER_NAME}-common ${LIBS})
