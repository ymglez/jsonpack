/**
 *  Jsonpack - Utils
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

#ifndef JSONPACK_JSON_HELPER_H
#define JSONPACK_JSON_HELPER_H

#include <string.h>

#include <jsonpack/3rdparty/format.h> //fast conversion from integers to string
#include <jsonpack/3rdparty/dtoa.hpp> //fast conversion from reals to string

#include "jsonpack/buffer.hpp"

/**
 * Integer size definitions
 */
#define INT_MAX_DIGITS	std::numeric_limits<int>::digits10 + 3
#define UINT_MAX_DIGITS std::numeric_limits<unsigned>::digits10 + 3

#define LONG_MAX_DIGITS		std::numeric_limits<long>::digits10 + 3
#define ULONG_MAX_DIGITS	std::numeric_limits<unsigned long>::digits10 + 3

#define LONGLONG_MAX_DIGITS		std::numeric_limits<long long>::digits10 + 3
#define ULONGLONG_MAX_DIGITS	std::numeric_limits<unsigned long long>::digits10 + 3

/**
 * Real size definitions
 * TODO fix 
 */
#define FLOAT_MAX_DIGITS	64
#define DOUBLE_MAX_DIGITS	64


JSONPACK_API_BEGIN_NAMESPACE
UTIL_BEGIN_NAMESPACE

static inline std::string trim(std::string s)
{
    s.erase(std::remove(s.begin(), s.end(), ' '),
                   s.end());
    return s;
}

/**
 * escaped characters
 */
#define NULL_CHAR_32 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
    static const char escaped[256] = {
        NULL_CHAR_32, 0, 0,'\"', 0, 0, 0, 0, '\'', 0, 0, 0, 0, 0, 0, 0, 0,
        NULL_CHAR_32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'\\', 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,'\n', 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        NULL_CHAR_32, NULL_CHAR_32, NULL_CHAR_32, NULL_CHAR_32
    };
#undef NULL_CHAR_32

/**
 * helper for stringify values
 */
struct json_builder
{
    static inline void append_value(buffer &json, const char* key, const char* value)
    {
        json.append("\"" , 1);
        json.append( key, strlen(key) ); //key
        json.append("\":", 2);
        json.append( value, strlen(value) ); //value
        json.append(",", 1);
    }

    static inline void append_string(buffer &json, const char* value, const std::size_t &len)
    {
        if( value != nullptr )
        {
            json.append("\"", 1);

            for( unsigned i = 0; i < len ; ++i)
            {
                if( (sizeof(char) == 1 || unsigned(value[i]) < 256) && escaped[(unsigned char)value[i]] )
                {
                    json.append("\\", 1);   //escape
                    json.append(value + i, 1);
                }
                else
                    json.append(value + i, 1);
            }
            json.append("\",", 2);
        }
        else
        {
            json.append( "null,", 5);
        }
    }


    /**
     ***********************************  APPEND  **************************************
     ************************************************************************************/

    /**
     * Append integer value to json like ("key":value,)
     */
    template<typename Integer>
    static void append_integer(buffer &json, const char *key, const Integer &value)
    {
        fmt::FormatInt formater(value);

        json.append("\"" , 1);
        json.append( key, strlen(key) ); //key
        json.append("\":", 2);
        json.append( formater.c_str(), formater.size() ); //value
        json.append(",", 1);
    }

    /**
     * Append integer value to json like (value,)
     */
    template<typename Integer>
    static void append_integer(buffer &json, const Integer &value)
    {
        fmt::FormatInt formater(value);
        json.append( formater.c_str(), formater.size() ); //value
        json.append(",", 1);
    }


    /**
     * Append real value to json
     */
    template<typename Real>
    static void append_real(buffer &json, const char *key, const Real &value)
    {
        char buf[DOUBLE_MAX_DIGITS] ;

        dtoa_milo(value, buf);

        json.append("\"" , 1);
        json.append( key, strlen(key) ); //key
        json.append("\":", 2);
        json.append( buf, strlen(buf) ); //value
        json.append(",", 1);
    }

    template<typename Real>
    static void append_real(buffer &json, const Real &value)
    {
        char buf[DOUBLE_MAX_DIGITS] ; //signs

        dtoa_milo(value, buf);

        json.append( buf, strlen(buf) ); //value
        json.append(",", 1);
    }

};

JSONPACK_API_END_NAMESPACE // util
JSONPACK_API_END_NAMESPACE // jsonpack

#endif // JSONPACK_JSON_HELPER_H
