add_executable(utils-test utils-test.cpp)
target_link_libraries(utils-test ${PROJECT_NAME})

add_executable(utils-test-tr utils-test-tr.cpp)
target_link_libraries(utils-test-tr ${PROJECT_NAME})

if(UTILS_BUILD_JSON)
    add_executable(json-test json-test.cpp)
    target_link_libraries(json-test ${PROJECT_NAME} ${PROJECT_NAME}-json)
endif()
