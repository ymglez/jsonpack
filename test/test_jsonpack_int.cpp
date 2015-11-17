
#define BOOST_TEST_MAIN
#if !defined( WIN32 )
    #define BOOST_TEST_DYN_LINK
#endif

/**
 * Boost.test causes the following warning under GCC
 * error: base class 'struct boost::unit_test::ut_detail::nil_t' has
 * a non-virtual destructor [-Werror=effc++]
 */
#if defined __GNUC__
#pragma GCC diagnostic ignored "-Weffc++"
#endif

#include <boost/test/unit_test.hpp>

#include <jsonpack.hpp>
#include <limits>
#include <cstring>
#include <cstdio>

struct  TestInt
{
    int test_int = 0;
    DEFINE_JSON_ATTRIBUTES(test_int)
};


BOOST_AUTO_TEST_CASE(pack_int_maximum_finite_value)
{
    TestInt jsonpack_int;
    jsonpack_int.test_int = std::numeric_limits<int>::max();

    char * pack_string = jsonpack_int.json_pack();

    char expect_string[64];
    sprintf(expect_string, "{\"test_int\":%d}", std::numeric_limits<int>::max());

    BOOST_CHECK_EQUAL(pack_string, expect_string);

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_int_maximum_finite_value)
{
    TestInt jsonpack_int;

    char json[64];
    sprintf(json, "{\"test_int\":%d}", std::numeric_limits<int>::max());

    jsonpack_int.json_unpack(json, strlen(json));

    BOOST_CHECK_EQUAL(jsonpack_int.test_int, std::numeric_limits<int>::max());
}


BOOST_AUTO_TEST_CASE(pack_int_min_finite_value)
{
    TestInt jsonpack_int;
    jsonpack_int.test_int = std::numeric_limits<int>::min();

    char * pack_string = jsonpack_int.json_pack();

    char expect_string[64];
    sprintf(expect_string, "{\"test_int\":%d}", std::numeric_limits<int>::min());

    BOOST_CHECK_EQUAL(pack_string, expect_string);

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_int_min_finite_value)
{
    TestInt jsonpack_int;

    char json[64];
    sprintf(json, "{\"test_int\":%d}", std::numeric_limits<int>::min());

    jsonpack_int.json_unpack(json, strlen(json));

    BOOST_CHECK_EQUAL(jsonpack_int.test_int, std::numeric_limits<int>::min());
}
