set(INCROOT ${CMAKE_CURRENT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${CMAKE_CURRENT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

# add the  header path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(01_Test_install ${SRCROOT}/install_test.cpp)
target_link_libraries(01_Test_install ${LIBS})

#FILES
set(FILES_HEADER
    ${INCROOT}/Game.hpp
)

set(FILES_SRC
    ${SRCROOT}/Game.cpp
    ${SRCROOT}/main.cpp
)


add_executable(01_Introduction ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(01_Introduction ${LIBS})

