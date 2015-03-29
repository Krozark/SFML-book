set(INCROOT ${INCROOT}/fields)
set(SRCROOT ${SRCROOT}/fields)
# append in local scope
list(APPEND FILES_HEADER
    ${INCROOT}/AutoField.hpp
    ${INCROOT}/BooleanField.hpp
    ${INCROOT}/CharField.hpp
    ${INCROOT}/CharField.tpl
    ${INCROOT}/DateTimeField.hpp
    ${INCROOT}/DoubleField.hpp
    ${INCROOT}/FK.hpp
    ${INCROOT}/FK.tpl
    ${INCROOT}/FloatField.hpp
    ${INCROOT}/IntegerField.hpp
    ${INCROOT}/UnsignedIntegerField.hpp
    ${INCROOT}/ManyToMany.hpp
    ${INCROOT}/ManyToMany.tpl
    ${INCROOT}/TextField.hpp
)
# set in parent scope
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

list(APPEND FILES_SRC
    ${SRCROOT}/AutoField.cpp
    ${SRCROOT}/BooleanField.cpp
    ${SRCROOT}/DoubleField.cpp
    ${SRCROOT}/DateTimeField.cpp
    ${SRCROOT}/FloatField.cpp
    ${SRCROOT}/IntegerField.cpp
    ${SRCROOT}/UnsignedIntegerField.cpp
    ${SRCROOT}/TextField.cpp
)

add_subdirectory(private)

# set in parent scope
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)
