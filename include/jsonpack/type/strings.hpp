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

//-------------------------- CHAR* -----------------------------------

template<>
struct json_traits<char*>
{

    static void append(buffer &json, const char *key, const char* value)
    {
        json.append("\"" , 1);
        json.append( key, strlen(key) ); //"key"
        json.append("\":", 2);

        append(json, value);
    }

    static void append(buffer &json, const char* value)
    {
        if(value != nullptr)
        {
            json.append("\"", 1);
            json.append( value, strlen(value)); //value
            json.append("\",", 2);
        }
        else
        {
            json.append( "null," , 5 ); //null
        }
    }

};

template<>
struct json_traits<char*&>
{

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, char* &value)
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
                std::string msg = "Invalid string value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, char* &value)
    {

        position p = v._pos;

        if(p._type != JTK_NULL)
        {
            value = (char*)malloc( p._count + 1) ;
            if(!value) throw alloc_error();
            memcpy( value, json_ptr + p._pos, p._count);
            value[p._count] = '\0';
        }
        else
        {
           value = nullptr;
        }

    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_STRING_LITERAL || v._pos._type == JTK_NULL ) );
    }

};

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
            json.append("\"", 1);
            json.append( value.c_str(), value.length() );
            json.append("\",", 2);
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

    static void extract(const jsonpack::value &v, char* json_ptr, std::string &value)
    {
        position p = v._pos;
        if(p._type != JTK_NULL)
        {
            value.resize(p._count);
            memcpy( const_cast<char*>(value.data()), json_ptr+ p._pos, p._count); // FIX undefined behavior
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

