set(INCROOT ${INCROOT}/Sqlite3)
set(SRCROOT ${SRCROOT}/Sqlite3)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Sqlite3DB.hpp
    ${INCROOT}/Sqlite3Query.hpp
    ${INCROOT}/Sqlite3TableCreator.hpp
)

list(APPEND FILES_SRC
    ${SRCROOT}/Sqlite3DB.cpp
    ${SRCROOT}/Sqlite3Query.cpp
    ${SRCROOT}/Sqlite3TableCreator.cpp
)

add_subdirectory(sqlite)

# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)


