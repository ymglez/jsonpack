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


BOOST_AUTO_TEST_CASE(pack_reals_maximum_finite_value)
{
    TestReal jsonpack_real;
    jsonpack_real.test_float = std::numeric_limits<float>::max();
	jsonpack_real.test_double = std::numeric_limits<double>::max();

    char * pack_string = jsonpack_real.json_pack();

    std::ostringstream formatter;
    formatter << "{\"test_float\":" << std::setprecision(17) << std::numeric_limits<float>::max()
        << ",\"test_double\":" << std::setprecision(17) << std::numeric_limits<double>::max() << "}";

	BOOST_CHECK_EQUAL(pack_string, formatter.str().c_str() );

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_reals_maximum_finite_value)
{
    TestReal jsonpack_real;

    std::ostringstream formatter;
    formatter << "{\"test_float\":" << std::setprecision(17) << std::numeric_limits<float>::max()
        << ",\"test_double\":" << std::setprecision(17) << std::numeric_limits<double>::max() << "}";

	jsonpack_real.json_unpack(formatter.str().c_str() , formatter.str().length() );

    BOOST_CHECK_EQUAL(jsonpack_real.test_float, std::numeric_limits<float>::max());
	BOOST_CHECK_EQUAL(jsonpack_real.test_double, std::numeric_limits<double>::max());
}


BOOST_AUTO_TEST_CASE(pack_reals_min_finite_value)
{
	TestReal jsonpack_real;
	jsonpack_real.test_float = std::numeric_limits<float>::min();
	jsonpack_real.test_double = std::numeric_limits<double>::min();


    char * pack_string = jsonpack_real.json_pack();

    std::ostringstream formatter;
    formatter << "{\"test_float\":" << std::setprecision(17) << std::numeric_limits<float>::min()
        << ",\"test_double\":" << std::setprecision(17) << std::numeric_limits<double>::min() << "}";

	BOOST_CHECK_EQUAL(pack_string, formatter.str().c_str() );

    free(pack_string);
}

BOOST_AUTO_TEST_CASE(unpack_reals_min_finite_value)
{
    TestReal jsonpack_real;

    std::ostringstream formatter;
    formatter << "{\"test_float\":" << std::setprecision(17) << std::numeric_limits<float>::min()
        << ",\"test_double\":" << std::setprecision(17) << std::numeric_limits<double>::min() << "}";

	jsonpack_real.json_unpack(formatter.str().c_str(), formatter.str().length() );

	BOOST_CHECK_EQUAL(jsonpack_real.test_float, std::numeric_limits<float>::min());
	BOOST_CHECK_EQUAL(jsonpack_real.test_double, std::numeric_limits<double>::min());
}
