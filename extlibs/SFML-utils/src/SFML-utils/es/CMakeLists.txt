set(INCROOT ${INCROOT}/es)
set(SRCROOT ${SRCROOT}/es)

set(LIBS ${LIBS} utils)


set(FILES_HEADER
    ${INCROOT}/Application.hpp
    ${INCROOT}/Component.hpp
    ${INCROOT}/Component.tpl
    ${INCROOT}/Entity.hpp
    ${INCROOT}/Entity.tpl
    ${INCROOT}/EntityManager.hpp
    ${INCROOT}/EntityManager.tpl
    ${INCROOT}/System.hpp
    ${INCROOT}/System.tpl
)

set(FILES_SRC
    ${SRCROOT}/Entity.cpp
)

Compile("${PROJECT_NAME}-es" "" "")
