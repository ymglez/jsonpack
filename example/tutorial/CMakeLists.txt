SET(JSONPACK_TUTORIAL_NAME "tutorial")

SET(SOURCES tutorial.cpp)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

IF(APPLE)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 ${CMAKE_CXX_FLAGS}")
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64 ${CMAKE_CXX_FLAGS}")
ENDIF()

ADD_EXECUTABLE(${JSONPACK_TUTORIAL_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${JSONPACK_TUTORIAL_NAME} jsonpack)
