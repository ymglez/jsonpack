/**
 *  Jsonpack - Integers traits for json operations
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

#ifndef JSONPACK_INTEGERS_HPP
#define JSONPACK_INTEGERS_HPP


#include "jsonpack/config.hpp"
#include "jsonpack/type/json_traits_base.hpp"


JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

//**************************************************************
//************************** BOOL ******************************
//**************************************************************
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid boolean value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract( const jsonpack::value &v, char* UNUSED(json_ptr), bool &value)
    {
        position p = v._pos;
        value = ( p._type == JTK_TRUE );
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_TRUE || v._pos._type == JTK_FALSE ) );
    }

};

//**************************************************************
//************************** CHAR ******************************
//**************************************************************
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid char value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, char &value)
    {
        value = v._pos._type != JTK_NULL ? json_ptr[v._pos._pos] : 0;
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_STRING_LITERAL || v._pos._type == JTK_NULL ) );
    }
};

//**************************************************************
//*********************** INT **********************************
//**************************************************************
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid int value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, int &value)
    {

        position p = v._pos;

        if( p._count >= INT_MAX_DIGITS)
            throw type_error("Int out of range");

        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[LONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated

        long v_cpy = std::strtol(buffer, nullptr, 10);

        if(errno ||
                     v_cpy > std::numeric_limits<int>::max() ||
                     v_cpy < std::numeric_limits<int>::min() )
            throw type_error("Int out of range");
        value = v_cpy;

    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }

};

//**************************************************************
//*********************** UNSIGNED INT *************************
//**************************************************************
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid unsigned int value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, unsigned int &value)
    {
        position p = v._pos;

        if( p._count >= UINT_MAX_DIGITS)
            throw type_error("Unsigned int out of range");

        //TODO check for sign
        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[LONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';            //null-terminated

        unsigned long v_cpy = std::strtoul(buffer, nullptr, 10);

        if(errno || v_cpy > std::numeric_limits<unsigned int>::max() ) // check range
            throw type_error("Unsigned int out of range");
        value = v_cpy;
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }
};

//**************************************************************
//*********************** LONG *********************************
//**************************************************************
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid long int value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, long &value)
    {
        position p = v._pos;

        if( p._count >= LONG_MAX_DIGITS)
            throw type_error("Long out of range");

        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[LONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated

        value = std::strtol(buffer, nullptr, 10);

        if(errno) // check range
            throw type_error("Long out of range");
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
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
            if( match_token_type(found->second) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid unsigned long int value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, unsigned long &value)
    {
        position p = v._pos;

        if( p._count >= ULONG_MAX_DIGITS)
            throw type_error("Unsigned long out of range");

        //TODO check for sign
        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[ULONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated

        value = std::strtoul(buffer, nullptr, 10);

        if(errno) // check range
            throw type_error("Unsigned long out of range");

//        value = atol( buffer );
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }
};

//**************************************************************
//*********************** LONG LONG ***************************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<long long>
{

    static void append(buffer &json, const char *key, const long long &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const long long &value)
    {
        util::json_builder::append_integer(json, value);
    }

};

template<>
struct json_traits<long long&>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, long long &value)
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
                std::string msg = "Invalid long long value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, long long &value)
    {
        position p = v._pos;

        if( p._count >= LONGLONG_MAX_DIGITS)
            throw type_error("Long long out of range");

        //TODO check for sign
        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[LONGLONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated

        value = std::strtoull(buffer, nullptr, 10);

        if(errno) // check range
            throw type_error("Long long out of range");

    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }
};

//**************************************************************
//*********************** UNSIGNED LONG LONG *******************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<unsigned long long>
{

    static void append(buffer &json, const char *key, const unsigned long long &value)
    {
        util::json_builder::append_integer(json, key, value);
    }

    static void append(buffer &json, const unsigned long long &value)
    {
        util::json_builder::append_integer(json, value);
    }
};

template<>
struct json_traits<unsigned long long&>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, unsigned long long &value)
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
                std::string msg = "Invalid unsigned long long value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, unsigned long long &value)
    {
        position p = v._pos;

        if( p._count > ULONGLONG_MAX_DIGITS - 1)
            throw type_error("Unsigned long long out of range");

        //TODO check for sign
        char * str_value = json_ptr+p._pos;   //pointing to the start
        char buffer[ULONGLONG_MAX_DIGITS];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated

        value = std::strtoll(buffer, nullptr, 10);

        if(errno) // check range
            throw type_error("Long long out of range");

    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }
};


JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_INTEGERS_HPP

