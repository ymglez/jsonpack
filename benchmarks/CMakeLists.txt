INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}")

IF(APPLE OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 ${CMAKE_CXX_FLAGS}")
ENDIF()

IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -march=native -Wall -pedantic -Wextra -Weffc++ -Werror -O3 -finline-functions -finline-limit=64 ${CMAKE_CXX_FLAGS}")
ENDIF()

ADD_EXECUTABLE(jsonpack_benchmarks 
	benchmarks.cpp
	benchpress.hpp)

IF ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	ADD_DEFINITIONS(
		-D_CRT_SECURE_NO_WARNINGS
		-D_SCL_SECURE_NO_WARNINGS
		-wd4099 -w4244)
	TARGET_LINK_LIBRARIES(jsonpack_benchmarks jsonpack-static)

ELSE()
	TARGET_LINK_LIBRARIES(jsonpack_benchmarks jsonpack)
ENDIF()

INSTALL (DIRECTORY files
    DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
INSTALL (TARGETS jsonpack_benchmarks
    DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
