set(INCROOT ${INCROOT}/json)
set(SRCROOT ${SRCROOT}/json)


SET(BisonOutputSrc ${SRCROOT}/Parser.cpp)
set(BisonOutputInc ${SRCROOT}/Parser.hpp)
set(BisonOutputExtra ${SRCROOT}/stack.hh)
SET(FlexOutputSrc ${SRCROOT}/Lexer.cpp)

if(UTILS_BUILD_PARSER)
    FIND_PACKAGE(BISON REQUIRED)
    IF(BISON_FOUND)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${BisonOutputSrc} ${BisonOutputInc} ${BisonOutputExtra}
          COMMAND ${BISON_EXECUTABLE}
          --output=${BisonOutputSrc}
          --defines=${BisonOutputInc}
                  ${SRCROOT}/Parser.yy
          COMMENT "Generating Parser.cpp"
        )
        INSTALL( FILES ${BisonOutputExtra} ${BisonOutputInc} DESTINATION include/${PROJECT_NAME}/json )
    else()
        message( SEND_ERROR "Bison is required" )
    ENDIF()

    FIND_PACKAGE(FLEX REQUIRED)
    IF(FLEX_FOUND)
        ADD_CUSTOM_COMMAND(
            OUTPUT ${FlexOutputSrc}
          COMMAND ${FLEX_EXECUTABLE}
          --outfile=${FlexOutputSrc}
                  ${SRCROOT}/Lexer.lex
                  COMMENT "Generating Lexer.cpp"
        )
    else()
        message( SEND_ERROR "Flex is required" )
    ENDIF()
endif()

#ROOT files
set(ROOT_SRC
    ${SRCROOT}/Array.cpp
    ${SRCROOT}/Driver.cpp
    ${SRCROOT}/Object.cpp
    ${SRCROOT}/Scanner.cpp
    ${SRCROOT}/Value.cpp
    ${BisonOutputSrc}
    ${FlexOutputSrc}
)
set(ROOT_HEADER
    ${INCROOT}/Array.hpp
    ${INCROOT}/Driver.hpp
    ${INCROOT}/FlexLexer.hpp
    ${INCROOT}/Object.hpp
    ${INCROOT}/Scanner.hpp
    ${INCROOT}/Value.hpp
    ${INCROOT}/Parser.hpp
    ${INCROOT}/stack.hh
)
set(ROOT_FILES
    ${ROOT_HEADER}
    ${ROOT_SRC}
)

#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

Compile("${PROJECT_NAME}-json" ${PROJECT_NAME} "${PROJECT_NAME}-static")




