CMAKE_MINIMUM_REQUIRED( VERSION 2.8)

PROJECT(jsonpack)

SET(LIB_MAJOR_VERSION "0")
SET(LIB_MINOR_VERSION "0")
SET(LIB_PATCH_VERSION "1")
SET(LIB_VERSION_STRING "${LIB_MAJOR_VERSION}.${LIB_MINOR_VERSION}.${LIB_PATCH_VERSION}")


IF (NOT CMAKE_BUILD_TYPE)
    MESSAGE(STATUS "No build type selected, defaulting to release with debug info")
    SET(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build Type")
ENDIF ()


OPTION(JSONPACK_BUILD_DOC "Build jsonpack documentation." OFF)
OPTION(JSONPACK_BUILD_EXAMPLES "Build jsonpack examples." OFF)

SET (prefix ${CMAKE_INSTALL_PREFIX})
SET (exec_prefix "\${prefix}")
SET (libdir "\${exec_prefix}/lib")
SET (includedir "\${prefix}/include")

IF(UNIX OR CYGWIN)
    SET(_CMAKE_INSTALL_DIR "${LIB_INSTALL_DIR}/cmake/${PROJECT_NAME}")
ELSEIF(WIN32)
    SET(_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/cmake")
ENDIF()
SET(CMAKE_INSTALL_DIR "${_CMAKE_INSTALL_DIR}" CACHE PATH "The directory cmake fiels are installed in")

# TODO documentation
if(JSONPACK_BUILD_DOC)
    add_subdirectory(doc)
endif()

# TODO example
if(JSONPACK_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()



SET (3rdparty_SOURCES src/3rdparty/format.cpp)

LIST (APPEND jsonpack_SOURCES
    src/parser.cpp
    src/3rdparty/format.cpp
)

LIST (APPEND jsonpack_HEADERS
    include/jsonpack.hpp
    include/jsonpack/buffer.hpp
    include/jsonpack/exceptions.hpp
    include/jsonpack/namespace.hpp
    include/jsonpack/object.hpp
    include/jsonpack/parser.hpp
    include/jsonpack/types.hpp
    include/jsonpack/util/builder.hpp
    include/jsonpack/type/integers.hpp
    include/jsonpack/type/reals.hpp
    include/jsonpack/type/simple_type.hpp
    include/jsonpack/type/strings.hpp
    include/jsonpack/type/json_traits_base.hpp
    include/jsonpack/type/sequences/sequences.hpp
    include/jsonpack/3rdparty/dtoa.hpp
    include/jsonpack/3rdparty/format.h
    include/jsonpack/serializer/serializer_cpp03.h
    include/jsonpack/serializer/serializer_cpp11.hpp
)

EXECUTE_PROCESS (
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/src/${PROJECT_NAME}
)

# pkg-config
CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.pc.in
                ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
                @ONLY)


INCLUDE_DIRECTORIES (
    ./
    include/
    ${CMAKE_CURRENT_BINARY_DIR}/include/
)


ADD_LIBRARY (jsonpack SHARED
    ${jsonpack_SOURCES}
    ${jsonpack_HEADERS}
)

ADD_LIBRARY (jsonpack-static STATIC
    ${jsonpack_SOURCES}
    ${jsonpack_HEADERS}
)

SET_TARGET_PROPERTIES (jsonpack-static PROPERTIES OUTPUT_NAME "jsonpack")
SET_TARGET_PROPERTIES (jsonpack PROPERTIES IMPORT_SUFFIX "_import.lib")
SET_TARGET_PROPERTIES (jsonpack PROPERTIES SOVERSION 3 VERSION 4.0.0)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET_PROPERTY (TARGET jsonpack APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64")
    SET_PROPERTY (TARGET jsonpack-static APPEND_STRING PROPERTY COMPILE_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64")

    # disabiling 3rdparty's warnings
    SET_SOURCE_FILES_PROPERTIES(${3rdparty_SOURCES} PROPERTIES COMPILE_FLAGS "-Wno-error -Wno-extra -Wno-effc++")
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    ADD_DEFINITIONS(-D_VARIADIC_MAX=10
                    -D_CRT_SECURE_NO_WARNINGS
                    -D_SCL_SECURE_NO_WARNINGS
                    -wd4800 -wd4804 -wd4018) # disabiling 3rdparty's warnings


    IF (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        STRING(REGEX REPLACE "/W[0-4]" "/W3" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    ELSE ()
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
    ENDIF ()
ENDIF ()

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC90" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC10" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC11")
    SET_SOURCE_FILES_PROPERTIES(${msgpack_SOURCES} PROPERTIES LANGUAGE CXX)
ENDIF()


INSTALL (TARGETS jsonpack jsonpack-static DESTINATION "${CMAKE_INSTALL_PREFIX}/lib")
INSTALL (DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_PREFIX}/include")
INSTALL (FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
    DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig"
    COMPONENT pkgconfig)




