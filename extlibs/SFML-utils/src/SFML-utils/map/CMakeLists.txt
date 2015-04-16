set(INCROOT ${INCROOT}/map)
set(SRCROOT ${SRCROOT}/map)

set(LIBS ${LIBS} ${PROJECT_NAME}-core utils-json)

set(FILES_HEADER
    ${INCROOT}/Configuration.hpp
    ${INCROOT}/Layer.hpp
    ${INCROOT}/Layer.tpl
    ${INCROOT}/Map.hpp
    ${INCROOT}/MapViewer.hpp
    ${INCROOT}/Map.tpl
    ${INCROOT}/Tile.hpp
    ${INCROOT}/Tile.tpl
    ${INCROOT}/VLayer.hpp
    ${INCROOT}/VMap.hpp

    ${INCROOT}/tileShapes/HexaIso.hpp
    ${INCROOT}/tileShapes/Hexa.hpp
    ${INCROOT}/tileShapes/Square.hpp
    ${INCROOT}/tileShapes/SquareIso.hpp
)

set(FILES_SRC
    ${SRCROOT}/Configuration.cpp
    ${SRCROOT}/VMap.cpp
    ${SRCROOT}/MapViewer.cpp
    ${SRCROOT}/VLayer.cpp

    ${SRCROOT}/tileShapes/HexaIso.cpp
    ${SRCROOT}/tileShapes/Hexa.cpp
    ${SRCROOT}/tileShapes/Square.cpp
    ${SRCROOT}/tileShapes/SquareIso.cpp
)

Compile("${PROJECT_NAME}-map" "" "")
