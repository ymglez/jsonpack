/**
 *  Jsonpack - JSON syntax parser
 *
 *  Copyright (c) 2015 Yadiel Martinez Gonzalez <ymglez2015@gmail.com>
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef JSONPACK_JSON_PARSER
#define JSONPACK_JSON_PARSER

#include <cctype>
#include <stdint.h>
#include <string>
#include <vector>

#include "jsonpack/namespace.hpp"

JSONPACK_API_BEGIN_NAMESPACE

/**
 * Forward
 */
struct key;
struct value;
struct key_hash;
enum jsonpack_token_type : unsigned;

template<class _Key, class _Value, class _Hasher>
class umap;

template<typename _Tp>
class vector;

typedef umap<key, value, key_hash> object_t;
typedef vector<value>  array_t;

/** ****************************************************************************
 ******************************** SCANNER **************************************
 *******************************************************************************/

struct scanner
{

    scanner():
        _source(nullptr),
        _i(0),
        _size(0),
        _start_token_pos(0),
        _c('\0')
    {}

    scanner(const scanner &s):
        _source(s._source),
        _i(s._i),
        _size(s._size),
        _start_token_pos(s._start_token_pos),
        _c(s._c)
    {}

    ~scanner()
    {
        _source = nullptr;
    }

    scanner& operator=(const jsonpack::scanner& s)
    {
        _source = s._source;
        return *this;
    }

    void init(const char *json, const std::size_t &len);

    void advance();

    /**
     * Parse the current value in json string
     */
    jsonpack_token_type next();

    /**
     * Parse a string literal
     */
    jsonpack_token_type string_literal();

    /**
     * Parse a other literal values like: TRUE, NULL
     */
    jsonpack_token_type other_value();

    /**
     * Parse a number
     */
    jsonpack_token_type number();


    /**
     * Helper functions to get key and position objects
     */
    key get_last_key(bool expect_str_literal);
    value get_last_value(bool expect_str_literal);


    //disabling warning on GNU
#ifndef _MSC_VER
    const char * _source = nullptr;
    uint_fast32_t _i = 0;
    uint_fast32_t _size = 0;

    uint_fast32_t _start_token_pos = 0;

    char _c = '\0';
#else
    const char * _source ;
    uint_fast32_t _i ;
    uint_fast32_t _size ;

    uint_fast32_t _start_token_pos ;

    char _c;
#endif

};

/** ****************************************************************************
 ******************************** PARSER ***************************************
 *******************************************************************************/
struct parser
{
	/**
	 * Default constructor
	 */
    parser();

	/**
	 * Copy constructor
	 */
    parser(const parser &p);

    bool json_validate(const char *json, const std::size_t &len, object_t & members);
    bool json_validate(const char *json,const std::size_t &len, array_t &elemets );

    std::string err_msg();

    /**
     * Function to free array_t
     */
    static void delete_array(array_t *arr);


    /**
     * Function to free object_t
     */
    static void delete_object(object_t *obj);

    /**
     * Function to free internal elements in object
     */
    static void clear(object_t* obj);

    /**
     * Function to free internal elements in array
     */
    static void clear(array_t* arr);

private:
    bool match(const jsonpack_token_type &token);

    void advance();

    bool item_list(object_t &members);

    bool item(object_t &members);

    bool value(key k, object_t &members);

    bool value(array_t &elemets);

    bool array_list(array_t &elemets);


    jsonpack_token_type _tk;
    scanner _s;

};

JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_JSON_PARSER
