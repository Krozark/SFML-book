set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

add_subdirectory(core)
add_subdirectory(es)
add_subdirectory(gui)
add_subdirectory(map)

if(SFML_UTILS_BUILD_BOX2D)
    add_subdirectory(box2D)
endif()

file(GLOB DEPLOY_FILES_AND_DIRS ${PROJECT_SOURCE_DIR}/include/*)
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION include/ )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/ )

