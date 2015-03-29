set(INCROOT ${INCROOT}/backends)
set(SRCROOT ${SRCROOT}/backends)

# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/DB.hpp
    ${INCROOT}/DB.tpl
    ${INCROOT}/op.hpp
    ${INCROOT}/Query.hpp
    ${INCROOT}/Query.tpl
)

list(APPEND FILES_SRC
    ${SRCROOT}/DB.cpp
    ${SRCROOT}/op.cpp
    ${SRCROOT}/Query.cpp
)

if(ORM_BUILD_SUPPORT_SQLITE3)
	list(APPEND FILES_HEADER
		${INCROOT}/Sqlite3.hpp
	)
	add_subdirectory(Sqlite3)
endif()

if(ORM_BUILD_SUPPORT_MYSQL)
	list(APPEND FILES_HEADER
	    ${INCROOT}/MySql.hpp
	)
	add_subdirectory(MySql)
endif()

add_subdirectory(private)

# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
