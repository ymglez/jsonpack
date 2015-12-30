/**
 *  Jsonpack - Reals traits for json operations
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

#ifndef JSONPACK_REALS_HPP
#define JSONPACK_REALS_HPP

#include "jsonpack/type/json_traits_base.hpp"


JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

//--------------------- FLOAT + DOUBLE ----------------------------
template<typename T>
struct json_traits<T, typename std::enable_if<std::is_floating_point<T>::value>::type>
{

    static void append(buffer &json, const char *key, const T &value)
    {
        util::json_builder::append_real(json, key, value);
    }

    static void append(buffer &json, const T &value)
    {
        util::json_builder::append_real(json, value);
    }
};

//-------------------------- FLOAT --------------------------------
template<>
struct json_extract_traits<float&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, float &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid float value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* UNUSED(json_ptr), float &value)
    {
        position p = v._pos;

//        char * str_value = json_ptr + p._pos;   //pointing to the start
        char * str_value = p._pos;   //pointing to the start

        char buffer[DOUBLE_MAX_DIGITS];
        const unsigned long len = p._count < DOUBLE_MAX_DIGITS ? p._count : DOUBLE_MAX_DIGITS - 1 ;
        memcpy(buffer, str_value, len);
        buffer[len] = '\0';    //null-terminated

#ifndef _MSC_VER
        value = std::strtof(buffer, nullptr);
        if(errno == ERANGE) // check range
            throw type_error("Float out of range");
#else
        double v_cpy = std::strtod(buffer, nullptr);
        if((errno == ERANGE) ||
                v_cpy > std::numeric_limits<float>::max() ||
                v_cpy < std::numeric_limits<float>::min() )
            throw type_error("Float out of range");
        value = static_cast<float>(v_cpy);
#endif
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ) );
    }

};

//-------------------------- DOUBLE --------------------------------


template<>
struct json_extract_traits<double&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, double &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid double value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* UNUSED(json_ptr), double &value)
    {
        position p = v._pos;
//        char * str_value = json_ptr + p._pos;   //pointing to the start
        char * str_value = p._pos;   //pointing to the start

        char buffer[DOUBLE_MAX_DIGITS];
        const unsigned long len = p._count < DOUBLE_MAX_DIGITS ? p._count : DOUBLE_MAX_DIGITS - 1 ;
        memcpy(buffer, str_value, len);
        buffer[len] = '\0';     //null-terminated

        value = std::strtod(buffer, nullptr);

        if(errno == ERANGE) // check range
            throw type_error("Double out of range");
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ) );
    }


};

JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_REALS_HPP

