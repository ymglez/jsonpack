INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include")

IF(APPLE)
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 ${CMAKE_CXX_FLAGS}")
ELSE()
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64 ${CMAKE_CXX_FLAGS}")
ENDIF()

#
# ADD TEST
#
ADD_EXECUTABLE(test_jsonpack_int test_jsonpack_int.cpp)


TARGET_LINK_LIBRARIES(test_jsonpack_int
    jsonpack
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

ADD_TEST(NAME test-pack-unpack-int
    COMMAND test_jsonpack_int)
