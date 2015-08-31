/**
 *  Jsonpack - Strings traits for json operations
 *
 *  Copyright (c) 2015 Yadiel Martinez Gonlazez <ymglez2015@gmail.com>
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

JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

//-------------------------- STD::STRING -----------------------------------

template<>
struct json_traits<std::string>
{

    static void append(buffer &json, const char *key, const std::string &value)
    {
        json.append("\"" , 1);
        json.append( key, strlen(key) ); //key
        json.append("\":\"", 3);
        json.append( value.c_str() , value.length() ); //value
        json.append("\",", 2);
    }

    static void append(buffer &json, const std::string &value)
    {
        json.append("\"", 1);
        json.append( value.c_str() , value.length() ); //value
        json.append("\",", 2);
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
            extract(found->second, json_ptr, value);
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::string &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;
            value.resize(p._count);
            memcpy( const_cast<char*>(value.data()), json_ptr+ p._pos, p._count); // FIX undefined behavior
        }
        else
        {
            //type error
        }

    }


};


JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_STRINGS_HPP

