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
#include <ostream>
#include <iomanip>

struct  TestReal
{
    TestReal():
        test_float(0.0f),
        test_double(0.0)
    {}

    float test_float;
	double test_double;
	DEFINE_JSON_ATTRIBUTES(test_float, test_double)
};

BOOST_AUTO_TEST_CASE(pack_unpack_reals_maximum_finite_value)
{
    TestReal jsonpack_real, output;

    jsonpack_real.test_float = std::numeric_limits<float>::max();
	jsonpack_real.test_double = std::numeric_limits<double>::max();

    char * pack_string = jsonpack_real.json_pack();

	output.json_unpack(pack_string , strlen(pack_string));

    BOOST_CHECK_EQUAL(output.test_float, std::numeric_limits<float>::max());
	BOOST_CHECK_EQUAL(output.test_double, std::numeric_limits<double>::max());

	free(pack_string);
}

BOOST_AUTO_TEST_CASE(pack_unpack_reals_min_finite_value)
{
    TestReal jsonpack_real, output;

    jsonpack_real.test_float = std::numeric_limits<float>::min();
	jsonpack_real.test_double = std::numeric_limits<double>::min();

    char * pack_string = jsonpack_real.json_pack();

	output.json_unpack(pack_string , strlen(pack_string));

    BOOST_CHECK_EQUAL(output.test_float, std::numeric_limits<float>::min());
	BOOST_CHECK_EQUAL(output.test_double, std::numeric_limits<double>::min());
	
	free(pack_string);
}
