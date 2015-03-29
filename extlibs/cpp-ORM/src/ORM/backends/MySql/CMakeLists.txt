set(INCROOT ${INCROOT}/MySql)
set(SRCROOT ${SRCROOT}/MySql)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/MySqlDB.hpp
    ${INCROOT}/MySqlQuery.hpp
    ${INCROOT}/MySqlTableCreator.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/MySqlDB.cpp
    ${SRCROOT}/MySqlQuery.cpp
    ${SRCROOT}/MySqlTableCreator.cpp
)
# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
