set(INCROOT ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${PROJECT_NAME})

if(UTILS_BUILD_JSON)
    add_subdirectory(json)
endif()

set(ROOT_SRC
    ${SRCROOT}/functional.cpp
    ${SRCROOT}/log.cpp
    ${SRCROOT}/plot.cpp
    ${SRCROOT}/string.cpp
    ${SRCROOT}/sys.cpp
    ${SRCROOT}/thread.cpp
    ${SRCROOT}/memory.cpp
)

set(ROOT_HEADER
    ${INCROOT}/functional.hpp
    ${INCROOT}/functional.tpl
    ${INCROOT}/json.hpp
    ${INCROOT}/log.hpp
    ${INCROOT}/log.tpl
    ${INCROOT}/maths.hpp
    ${INCROOT}/maths.tpl
    ${INCROOT}/plot.hpp
    ${INCROOT}/plot.tpl
    ${INCROOT}/string.hpp
    ${INCROOT}/string.tpl
    ${INCROOT}/sys.hpp
    ${INCROOT}/sys.tpl
    ${INCROOT}/thread.hpp
    ${INCROOT}/thread.tpl
    ${INCROOT}/memory.hpp
    ${INCROOT}/memory.tpl
    ${INCROOT}/tr.hpp
)


set(ROOT_FILES
    ${ROOT_HEADER}
    ${ROOT_SRC}
)

#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

Compile("${PROJECT_NAME}" "" "" )

file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} ${BisonOutputInc} DESTINATION include/${PROJECT_NAME} )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${PROJECT_NAME} )

