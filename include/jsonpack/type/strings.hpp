/**
 *  Jsonpack - Strings traits for json operations
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

#ifndef JSONPACK_STRINGS_HPP
#define JSONPACK_STRINGS_HPP

#include <algorithm>

#include "jsonpack/type/json_traits_base.hpp"
#include "jsonpack/util/utf8.hpp"

JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE


//-------------------------- STD::STRING -----------------------------------

template<>
struct json_traits<std::string>
{

    static void append(buffer &json, const char *key, const std::string &value)
    {
        json.append("\"" , 1);
        json.append( key, strlen(key) ); //"key"
        json.append("\":", 2);

        append(json, value);
    }

    static void append(buffer &json, const std::string &value)
    {
        if(! value.empty() )    //:"value"
        {
            util::json_builder::append_string(json, value.c_str(), value.length() );
        }
        else                    //:null
        {
            json.append( "null,", 5);
        }
    }

};

template<>
struct json_traits<std::string&>
{

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::string &value)
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
                std::string msg = "Invalid std::string value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* UNUSED(json_ptr), std::string &value)
    {
        position p = v._pos;
        if(p._type != JTK_NULL)
        {
            // pritty but slow and dangerous

            //            value.resize(p._count);
            //            memcpy( const_cast<char*>(value.data()), json_ptr+ p._pos, p._count); // FIX undefined behavior

            //            unsigned i = 0;
            //            value.erase(std::remove_if(value.begin(), value.end(),
            //                        [&i, value](char c)->bool
            //                        {
            //                            bool esc = ( c == '\\' && (i < value.length()-1 ) && (sizeof(char) == 1 || unsigned(value[i+1]) < 256) && util::escaped[(unsigned char)value[i+1]] );
            //                            i++;
            //                            return esc;
            //                        }),
            //                        value.end() );


            //hard coded but fast and safe

            if (value.capacity() <  p._count + 1)
                value.reserve(p._count + 1);

            char* val_ptr = p._pos;
            for(char* i = val_ptr ; i != val_ptr + p._count ; ++i)
            {
                char c = *i;
                if( c == '\\' )
                {
                    c = *(++i);

                    switch (c)
                    {
                    case '"':
                    case '\\':
                    case '/':
                        value.push_back( (char)c );
                        break;
                    case 'b':
                        value.push_back('\b');
                        break;
                    case 'f':
                        value.push_back('\f');
                        break;
                    case 'n':
                        value.push_back('\n');
                        break;
                    case 'r':
                        value.push_back('\r');
                        break;
                    case 't':
                        value.push_back('\t');
                        break;
                    default: // 'u' unicode escape
                        uint16_t uc = 0, lc = 0;
                        util::utf8::uchar_t codepoint;

                        util::str::parse_hex(i, uc);

                        if (uc >= 0xD800 && uc <= 0xDFFF)
                        {
                            /* Handle UTF-16 surrogate pair. */
                            if (*i++ != '\\' || *i++ != 'u' || !util::str::parse_hex(i, lc))
                                throw type_error("Incomplete surrogate pair");

                            if (!util::utf8::from_surrogate_pair(uc, lc, codepoint))
                                throw type_error("Invalid surrogate pair");
                        }
                        else if (uc == 0)
                        {
                            throw type_error("Unicode disallow \\u0000");
                        }
                        else
                        {
                            codepoint = uc;
                        }

                        char b[4];
                        int len = util::utf8::write_char(codepoint, b);

                        value.append(b, len);

                        i += 4;
                        break;

                    }
                }
                else
                {
                    /* Validate and echo a UTF-8 character. */
//                    size_t len;

//                    i--;
//                    len = util::utf8::validate_char(i);
//                    if (len == 0)
//                        throw invalid_json("Invalid UTF-8 character");

                    value.push_back(c);
                }
            }
        }
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_STRING_LITERAL || v._pos._type == JTK_NULL ) );
    }


};


JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_STRINGS_HPP

