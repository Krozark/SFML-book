set(INCROOT ${INCROOT}/gui)
set(SRCROOT ${SRCROOT}/gui)

set(TARGET sfml-gui)

# add the  header path
#FILES
set(FILES_HEADER
)

set(FILES_SRC
)

add_library(${TARGET}$ STATIC ${FILES_HEADER} ${FILES_SRC})
set_target_properties(${TARGET}
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
    )
target_link_libraries(${TARGET} ${LIBS})
INSTALL(TARGETS ${TARGET}
    DESTINATION lib
    )
