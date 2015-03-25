set(INCROOT ${INCROOT}/core)
set(SRCROOT ${SRCROOT}/core)

set(FILES_HEADER
    ${INCROOT}/Action.hpp
    ${INCROOT}/ActionMap.hpp
    ${INCROOT}/ActionMap.tpl
    ${INCROOT}/ActionTarget.hpp
    ${INCROOT}/ActionTarget.tpl
    ${INCROOT}/ResourceManager.hpp
    ${INCROOT}/ResourceManager.tpl

    ${INCROOT}/Animation.hpp
    ${INCROOT}/AnimatedSprite.hpp
)

set(FILES_SRC
    ${SRCROOT}/Action.cpp

    ${SRCROOT}/Animation.cpp
    ${SRCROOT}/AnimatedSprite.cpp
)

Compile("${PROJECT_NAME}-core" "" "")
