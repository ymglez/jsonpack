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
    TestInt():
        test_int(0),
        test_long(0),
        test_llong(0)
    {}

    int test_int;
    long test_long;
    long long test_llong;
	DEFINE_JSON_ATTRIBUTES(test_int,test_long, test_llong)
};


BOOST_AUTO_TEST_CASE(pack_integers_maximum_finite_value)
{
    TestInt jsonpack_int;
    jsonpack_int.test_int = std::numeric_limits<int>::max();
	jsonpack_int.test_long = std::numeric_limits<long>::max();
	jsonpack_int.test_llong = std::numeric_limits<long long>::max();

    char * pack_string = jsonpack_int.json_pack();

    char expect_string[128];
    sprintf(expect_string, "{\"test_int\":%d,\"test_long\":%ld,\"test_llong\":%lld}",
            std::numeric_limits<int>::max(),
            std::numeric_limits<long>::max(),
            std::numeric_limits<long long>::max()
            );

    BOOST_CHECK_EQUAL(pack_string, expect_string);

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_integers_maximum_finite_value)
{
    TestInt jsonpack_int;

    char json[128];
    sprintf(json, "{\"test_int\":%d,\"test_long\":%ld,\"test_llong\":%lld}",
            std::numeric_limits<int>::max(),
            std::numeric_limits<long>::max(),
            std::numeric_limits<long long>::max()
            );

    jsonpack_int.json_unpack(json, strlen(json));

    BOOST_CHECK_EQUAL(jsonpack_int.test_int, std::numeric_limits<int>::max());
	BOOST_CHECK_EQUAL(jsonpack_int.test_long, std::numeric_limits<long>::max());
	BOOST_CHECK_EQUAL(jsonpack_int.test_llong, std::numeric_limits<long long>::max());
}


BOOST_AUTO_TEST_CASE(pack_integers_min_finite_value)
{
    TestInt jsonpack_int;
    jsonpack_int.test_int = std::numeric_limits<int>::min();
	jsonpack_int.test_long = std::numeric_limits<long>::min();
	jsonpack_int.test_llong = std::numeric_limits<long long>::min();

    char * pack_string = jsonpack_int.json_pack();

    char expect_string[128];
    sprintf(expect_string, "{\"test_int\":%d,\"test_long\":%ld,\"test_llong\":%lld}",
            std::numeric_limits<int>::min(),
            std::numeric_limits<long>::min(),
            std::numeric_limits<long long>::min()
            );

    BOOST_CHECK_EQUAL(pack_string, expect_string);

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_integers_min_finite_value)
{
    TestInt jsonpack_int;

    char json[128];
    sprintf(json, "{\"test_int\":%d,\"test_long\":%ld,\"test_llong\":%lld}",
            std::numeric_limits<int>::min(),
            std::numeric_limits<long>::min(),
            std::numeric_limits<long long>::min()
            );

    jsonpack_int.json_unpack(json, strlen(json));

    BOOST_CHECK_EQUAL(jsonpack_int.test_int, std::numeric_limits<int>::min());
	BOOST_CHECK_EQUAL(jsonpack_int.test_long, std::numeric_limits<long>::min());
	BOOST_CHECK_EQUAL(jsonpack_int.test_llong, std::numeric_limits<long long>::min());
}
