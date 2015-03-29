set(INCROOT ${INCROOT}/private)
set(SRCROOT ${SRCROOT}/private)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Filter.hpp
    ${INCROOT}/Filter.tpl
    ${INCROOT}/M2MFilter.hpp
    ${INCROOT}/M2MFilter.tpl
    ${INCROOT}/FilterSet.hpp
    ${INCROOT}/FilterSet.tpl
    ${INCROOT}/M2MQuerySet.hpp
    ${INCROOT}/M2MQuerySet.tpl
    ${INCROOT}/QuerySet.hpp
    ${INCROOT}/QuerySet.tpl
    ${INCROOT}/TableCreator.hpp
    ${INCROOT}/VFilter.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/Filter.cpp
    ${SRCROOT}/TableCreator.cpp
    ${SRCROOT}/VFilter.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
