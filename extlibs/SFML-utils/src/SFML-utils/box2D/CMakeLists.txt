set(INCROOT ${INCROOT}/box2D)
set(SRCROOT ${SRCROOT}/box2D)

find_library(LIB_BOX2D Box2D)
set(LIBS ${LIBS} ${LIB_BOX2D})

#FILES
set(FILES_HEADER
    ${INCROOT}/DebugDraw.hpp
    ${INCROOT}/converter.hpp
)

set(FILES_SRC
    ${SRCROOT}/DebugDraw.cpp
)

Compile("${PROJECT_NAME}-box2D" ${LIB_BOX2D} ${LIB_BOX2D})
