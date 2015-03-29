set(INCROOT ${INCROOT}/private)
set(SRCROOT ${SRCROOT}/private)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/Attr.hpp
    ${INCROOT}/Attr.tpl
    ${INCROOT}/FKBase.hpp
    ${INCROOT}/FKBase.tpl
    ${INCROOT}/VAttr.hpp
    ${INCROOT}/VFK.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/VAttr.cpp
    ${SRCROOT}/VFK.cpp
)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
