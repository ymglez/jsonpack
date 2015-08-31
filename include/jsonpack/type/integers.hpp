/**
 *  Jsonpack - Integers traits for json operations
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

#ifndef JSONPACK_INTEGERS_HPP
#define JSONPACK_INTEGERS_HPP


#include "jsonpack/type/json_traits_base.hpp"


JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE


//-------------------------- BOOL -----------------------------------
/**
 *  bool type traits specialization
 */
template<>
struct json_traits<bool>
{
    static void append(buffer &json, const char *key, const bool &value)
    {
        util::json_builder::append_string(json, key, value ? "true" : "false");
    }

    static void append(buffer &json, const bool &value) //append value in array
    {
        json.append(value ? "true," : "false,", value ? 5 :6 );
    }

};

template<>
struct json_traits<bool&>
{

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, bool &value)
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

    static void extract(const jsonpack::value &v, char* json_ptr, bool &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;
            char * value_str = json_ptr+p._pos;   //pointing to the start
            value = ( memcmp(value_str, "true", 4) == 0 )||( memcmp(value_str, "TRUE", 4) == 0 );
        }
        else
        {
            //type error
        }
    }

};

//-------------------------- CHAR -----------------------------------
/**
 *  char type traits specialization
 */
template<>
struct json_traits<char>
{

    static void append(buffer &json, const char *key, const char &value)
    {
        if( std::isgraph(value) )
        {
            char c[4] = {'"', value, '"', '\0'};
            util::json_builder::append_string(json, key, c);
        }
        else
            util::json_builder::append_string(json, key, "null");
    }

    static void append(buffer &json, const char &value)
    {
        if( std::isgraph(value) )
        {
            char c[4] = {'"', value, '"', ','};
            json.append(c, 4);
        }
        else
            json.append("null,", 5);
    }
};

template<>
struct json_traits<char&>
{

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, char &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            extract(found->second, json_ptr, value );
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, char &value)
    {
        if(v._field == _POS) // check for null
        {
            value = json_ptr[v._pos._pos];
        }
        else
        {
            //type error
        }
    }
};
//-------------------------- INT -----------------------------------
/**
 *  int type traits specialization
 */
template<>
struct json_traits<int>
{

    static void append(buffer &json, const char *key, const int &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const int &value)
    {
        util::json_builder::append_integer(json, value);
    }
};

template<>
struct json_traits<int&>
{

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, int &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            extract(found->second, json_ptr, value );
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, int &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;

            char * str_value = json_ptr+p._pos;   //pointing to the start
            char buffer[LONG_MAX_DIGITS + 1];
            memcpy(buffer, str_value, p._count);
            buffer[p._count] = '\0';        //null-terminated

            value = atoi( buffer );             //converting value
        }
        else
        {
            //type error
        }
    }

};
//-------------------------- UNSIGNED INT --------------------------------
/**
 *  unsigned int type traits specialization
 */
template<>
struct json_traits<unsigned int>
{
    static void append(buffer &json, const char *key, const unsigned int &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const unsigned int &value)
    {
        util::json_builder::append_integer(json, value);
    }
};

template<>
struct json_traits<unsigned int&>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, unsigned int &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            extract(found->second, json_ptr, value );
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, unsigned int &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;

            char * str_value = json_ptr+p._pos;   //pointing to the start
            char buffer[LONG_MAX_DIGITS + 1];
            memcpy(buffer, str_value, p._count);
            buffer[p._count] = '\0';        //null-terminated

            value = atoi( buffer );              //converting value
        }
        else
        {
            //type error
        }
    }
};

//------------------------- LONG ----------------------------
/**
 *  long type traits specialization
 */
template<>
struct json_traits<long>
{
    static void append(buffer &json, const char *key, const long &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const long &value)
    {
        util::json_builder::append_integer(json, value);
    }
};

template<>
struct json_traits<long&>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, long &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            extract(found->second, json_ptr, value );
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, long &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;

            char * str_value = json_ptr+p._pos;   //pointing to the start
            char buffer[LONG_MAX_DIGITS + 1];
            memcpy(buffer, str_value, p._count);
            buffer[p._count] = '\0';        //null-terminated

            value = atol( buffer );

//            value = atol( str_value );              //converting value
        }
        else
        {
            //type error
        }
    }

};

//**************************************************************
//*********************** UNSIGNED LONG ************************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<unsigned long>
{

    static void append(buffer &json, const char *key, const unsigned long &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const unsigned long &value)
    {
        util::json_builder::append_integer(json, value);
    }

};

template<>
struct json_traits<unsigned long&>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, unsigned long &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            extract(found->second, json_ptr, value );
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, unsigned long &value)
    {
        if(v._field == _POS)
        {
            position p = v._pos;

            char * str_value = json_ptr+p._pos;   //pointing to the start
            char buffer[LONG_MAX_DIGITS + 1];
            memcpy(buffer, str_value, p._count);
            buffer[p._count] = '\0';        //null-terminated

            value = atol( buffer );
        }
        else
        {
            //type error
        }
    }
};


JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_INTEGERS_HPP

