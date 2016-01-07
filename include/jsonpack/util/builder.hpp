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
#include "jsonpack/util/utf8.hpp"
#include "jsonpack/config.hpp"

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

struct str
{
    static inline std::string trim(std::string s)
    {
        s.erase(std::remove(s.begin(), s.end(), ' '),
                s.end());
        return s;
    }

    static int write_hex(buffer &json, uint16_t val)
    {
        char out[4];
        const char *hex = "0123456789ABCDEF";

        out[0] = hex[(val >> 12) & 0xF];
        out[1] = hex[(val >> 8)  & 0xF];
        out[2] = hex[(val >> 4)  & 0xF];
        out[3] = hex[ val        & 0xF];

        json.append(out, 4);
        return 4;
    }

    static bool parse_hex(const char *sp, uint16_t &out)
    {
        const char *s = sp;
        uint16_t ret = 0;
        uint16_t i;
        uint16_t tmp;

        for (i = 0; i < 4; i++)
        {
            char c = *(++s);
            if (c >= '0' && c <= '9')
                tmp = (uint16_t)(c - '0');
            else if (c >= 'A' && c <= 'F')
                tmp = (uint16_t)(c - 'A' + 10);
            else if (c >= 'a' && c <= 'f')
                tmp = (uint16_t)(c - 'a' + 10);
            else
                return false;

            ret = (uint16_t)((ret << 4) + tmp);
        }

        out = ret;
        sp = s;
        return true;
    }
};

/**
 * helper for stringify values
 */
struct json_builder
{
    static inline void append_value(buffer &json, const char* key, const char* value)
    {
        append_string(json, key, strlen(key));
        json.erase_last_comma();
        json.append(":", 1);
		json.append(value, strlen(value) );
		json.append(",", 1);
    }

    static inline void append_string(buffer &json, const char* value, const std::size_t &len)
    {
        if( value != nullptr )
        {
            json.append("\"", 1);

            unsigned i = 0;
            const char* str = value;
            while (/**str != 0*/ i < len)
            {
                char c = *str++;
                i++;

                switch (c)
                {
                case '"':
                    json.append("\\\"",2);
                    break;
                case '\\':
                    json.append("\\\\",2);
                    break;
                case '\b':
                    json.append("\\b",2);
                    break;
                case '\f':
                    json.append("\\f",2);
                    break;
                case '\n':
                    json.append("\\n",2);
                    break;
                case '\r':
                    json.append("\\r",2);
                    break;
                case '\t':
                    json.append("\\t",2);

                    break;
                default:
                    str--;
                    i--;

                    size_t count = utf8::validate_char(str);
                    if (count == 0)
                    {
                        throw invalid_json("Invalid utf-8");
                    }
                    else if (c < 0x1F)
                    {
                        /* Encode using \u.... */
                        uint32_t codepoint;
                        unsigned s = utf8::read_char(str, codepoint);
                        str+= s;
                        i+= s;

                        if (codepoint <= 0xFFFF)
                        {
                            json.append("\\u", 2);
                            str::write_hex(json, (uint16_t)codepoint);
                        }
                        else
                        {
                            /* Produce a surrogate pair. */
                            uint16_t uc, lc;

                            if(codepoint <= 0x10FFFF)
                                throw invalid_json("Invalid utf-8");

                            //assert(codepoint <= 0x10FFFF);

                            utf8::to_surrogate_pair(codepoint, uc, lc);

                            json.append("\\u", 2);
                            str::write_hex(json, uc);

                            json.append("\\u", 2);
                            str::write_hex(json, lc);
                        }
                    }
                    else
                    {
                        json.append(str, count);
                        str += count;
                        i+= count;
                    }

                    break;
                }
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
