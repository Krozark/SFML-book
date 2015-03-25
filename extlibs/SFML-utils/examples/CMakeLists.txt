set(INCROOT ${PROJECT_SOURCE_DIR}/examples)
set(SRCROOT ${PROJECT_SOURCE_DIR}/examples)

add_executable(core core.cpp)
target_link_libraries(core ${PROJECT_NAME}-core)

add_executable(gui gui.cpp)
target_link_libraries(gui ${PROJECT_NAME}-gui)

add_executable(map map.cpp)
target_link_libraries(map ${PROJECT_NAME}-map)

add_executable(es es.cpp)
target_link_libraries(es ${PROJECT_NAME}-es)


