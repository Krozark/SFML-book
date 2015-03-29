set(INCROOT ${PROJECT_SOURCE_DIR}/include/ORM)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/ORM)

set(FILES_HEADER
    ${INCROOT}/backends.hpp
    ${INCROOT}/debug.hpp
    ${INCROOT}/externals.hpp
    ${INCROOT}/fields.hpp
    ${INCROOT}/models.hpp
)
set(FILES_SRC)

add_subdirectory(backends)
add_subdirectory(core)
add_subdirectory(fields)
add_subdirectory(models)


#SHARED lib
add_library(orm-shared SHARED ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(orm-shared
    PROPERTIES
    OUTPUT_NAME orm
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(orm-shared ${LIBS})
INSTALL(TARGETS orm-shared
    DESTINATION lib
)

#static lib
add_library(orm-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(orm-static
    PROPERTIES
    OUTPUT_NAME orm
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(orm-static ${LIBS})
INSTALL(TARGETS orm-static
    DESTINATION lib
)

file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} DESTINATION include )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include )


