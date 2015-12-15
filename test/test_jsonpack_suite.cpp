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
#include <fstream>

#include <jsonpack.hpp>


BOOST_AUTO_TEST_CASE(unpack_object_fail_json_org)
{
    // test cases are from http://json.org/JSON_checker/
	std::string files[] = {
                    "json_tests/fail1.json",
                    "json_tests/fail3.json",
                    //"json_tests/fail9.json",	// {"Extra comma": true,}
                    //"json_tests/fail10.json",	// {"Extra value after close": true} "misplaced quoted value"
                    "json_tests/fail11.json",	
                    "json_tests/fail12.json",
                    //"json_tests/fail13.json",	// {"Numbers cannot have leading zeroes": 013}
                    //"json_tests/fail14.json",	// {"Numbers cannot be hex": 0x14}
                    "json_tests/fail19.json",
                    "json_tests/fail20.json",
                    "json_tests/fail21.json",
                    "json_tests/fail32.json",

				};

        for (auto filename : files)
        {
			std::ifstream inputs_json(filename);
			std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));

			jsonpack::object_t j;

			BOOST_CHECK_THROW(j.json_unpack(json.c_str(), json.length() ), jsonpack::invalid_json);
        }
    }


BOOST_AUTO_TEST_CASE(unpack_array_fail_json_org)
{
    // test cases are from http://json.org/JSON_checker/
	std::string files[] = {
                    "json_tests/fail2.json",
                    //"json_tests/fail4.json",  ["extra comma",]
                    //"json_tests/fail5.json",	["double extra comma",,]
                    "json_tests/fail6.json",
                    //"json_tests/fail7.json",	["Illegal backslash escape: \017"]
                    //"json_tests/fail8.json",	["Extra close"]]
                    //"json_tests/fail15.json",	["Illegal backslash escape: \x15"]
                    "json_tests/fail16.json",
                    //"json_tests/fail17.json", ["Illegal backslash escape: \017"]
                    //"json_tests/fail18.json",	// [[[[[[[[[[[[[[[[[[[["Too deep"]]]]]]]]]]]]]]]]]]]]
                    "json_tests/fail22.json",
                    "json_tests/fail23.json",
                    "json_tests/fail24.json",
                    //"json_tests/fail25.json",	// ["	tab	character	in	string	"]
                    //"json_tests/fail26.json",	// ["tab\   character\   in\  string\  "]
                    //"json_tests/fail27.json",	// ["line 
												//	break"]
                    //"json_tests/fail28.json",	// ["line\ 
												//	break"]
                    "json_tests/fail29.json",
                    "json_tests/fail30.json",
                    "json_tests/fail31.json",
                    "json_tests/fail33.json"
				};

        for (auto filename : files)
        {
			std::ifstream inputs_json(filename);
			std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));

			jsonpack::array_t j;

			BOOST_CHECK_THROW(j.json_unpack(json.c_str(), json.length() ), jsonpack::invalid_json);
        }
    }

BOOST_AUTO_TEST_CASE(unpack_object_success_json_org)
{
    // test cases are from http://json.org/JSON_checker/

	std::ifstream inputs_json("json_tests/pass3.json");
	std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));

	jsonpack::object_t j;

	BOOST_CHECK_NO_THROW(j.json_unpack(json.c_str(), json.length() ));  
}

BOOST_AUTO_TEST_CASE(unpack_array_success_json_org)
{
    // test cases are from http://json.org/JSON_checker/

	std::string files[] = {
		"json_tests/pass1.json",
		"json_tests/pass2.json"
				};

        for (auto filename : files)
        {
			std::ifstream inputs_json(filename);
			std::string json( (std::istreambuf_iterator<char>(inputs_json) ), (std::istreambuf_iterator<char>() ));

			jsonpack::array_t j;

			BOOST_CHECK_NO_THROW(j.json_unpack(json.c_str(), json.length() ));
		}
}