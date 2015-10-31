SET(JSONPACK_TUTORIAL_NAME "tutorial")

SET(SOURCES tutorial.cpp)

INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64 ${CMAKE_CXX_FLAGS}")

ADD_EXECUTABLE(${JSONPACK_TUTORIAL_NAME} ${SOURCES})

TARGET_LINK_LIBRARIES(${JSONPACK_TUTORIAL_NAME} jsonpack)
