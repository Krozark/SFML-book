set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)

set(LIBS ${LIBS} ${PROJECT_NAME}-core utils-json)

set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/HexaIso.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/MapViewer.hpp
    ${INCROOT}/Map.tpl
    ${INCROOT}/Tile.hpp
    ${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMap.hpp
)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/HexaIso.cpp
    ${SRCROOT}/VMap.cpp
    ${SRCROOT}/MapViewer.cpp
    ${SRCROOT}/VLayer.cpp
)

Compile("${PROJECT_NAME}-map" "" "")
