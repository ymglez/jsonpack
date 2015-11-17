INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include" "${Boost_INCLUDE_DIR}")

IF(APPLE OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 ${CMAKE_CXX_FLAGS}")
ENDIF()

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64 ${CMAKE_CXX_FLAGS}")
ENDIF()

#
# ADD TEST
#
ADD_EXECUTABLE(test_jsonpack_int test_jsonpack_int.cpp)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	TARGET_LINK_LIBRARIES(test_jsonpack_int
    jsonpack-static
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
ELSE()
	TARGET_LINK_LIBRARIES(test_jsonpack_int
    jsonpack
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)
ENDIF()



ADD_TEST(NAME test-pack-unpack-int
    COMMAND test_jsonpack_int)
