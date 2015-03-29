set(INCROOT ${INCROOT}/sqlite)
set(SRCROOT ${SRCROOT}/sqlite)

list(APPEND FILES_HEADER
    ${INCROOT}/sqlite3.h
)

list(APPEND FILES_SRC
    ${SRCROOT}/sqlite3.c
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)


