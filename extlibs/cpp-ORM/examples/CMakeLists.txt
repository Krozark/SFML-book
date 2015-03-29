set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)

add_executable(basic main.cpp)
target_link_libraries(basic ${LIBS} orm-shared)


