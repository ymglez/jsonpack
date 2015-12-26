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
struct json_traits<bool, void>
{
    static void append(buffer &json, const char *key, const bool &value)
    {
        util::json_builder::append_value(json, key, value ? "true" : "false");
    }

    static void append(buffer &json, const bool &value) //append value in array
    {
        json.append(value ? "true," : "false,", value ? 5 :6 );
    }

};

template<>
struct json_traits<bool&, void>
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
struct json_traits<char, void>
{

    static void append(buffer &json, const char *key, const char &value)
    {
        if( std::isgraph(value) )
        {
            char c[4] = {'"', value, '"', '\0'};
            util::json_builder::append_value(json, key, c);
        }
        else
            util::json_builder::append_value(json, key, "null");
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
struct json_traits<char&, void>
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

    static void extract(const jsonpack::value &v, char* UNUSED(json_ptr), char &value)
    {
//        value = v._pos._type != JTK_NULL ? json_ptr[v._pos._pos] : 0;
        value = v._pos._type != JTK_NULL ? *(v._pos._pos) : 0;
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_STRING_LITERAL || v._pos._type == JTK_NULL ) );
    }
};


template<class T, class int_t, int max_digits, class derived>
struct json_traits_int_common {
    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _POS &&
                (v._pos._type == JTK_INTEGER || v._pos._type == JTK_REAL ));
    }
    
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, T &value)
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
                std::string msg = derived::invalid_value_msg();
                throw type_error( msg.data() );
            }
        }
    }
    
    static void extract(const jsonpack::value &v, char* UNUSED(json_ptr), T &value)
    {
        position p = v._pos;
        
        if( p._count >= max_digits)
            throw type_error(derived::type_out_of_range());
        
        //        char * str_value = json_ptr+p._pos;   //pointing to the start
        char * str_value = p._pos;   //pointing to the start
        
        char buffer[max_digits];
        memcpy(buffer, str_value, p._count);
        buffer[p._count] = '\0';        //null-terminated
        
        int_t v_cpy = derived::str_to_int(buffer);
        if((errno == ERANGE) ||
           v_cpy > std::numeric_limits<int_t>::max() ||
           v_cpy < std::numeric_limits<int_t>::min() )
            throw type_error(derived::type_out_of_range());
        value = derived::int_to_value(v_cpy);
    }
    
};



#define HAS_MEM_FUNC(func, name)                                        \
    template<typename T, typename Sign>                                 \
    struct name {                                                       \
        typedef char yes[1];                                            \
        typedef char no [2];                                            \
        template <typename U, U> struct type_check;                     \
        template <typename _1> static yes &chk(type_check<Sign, &_1::func > *); \
        template <typename   > static no  &chk(...);                    \
        static bool const value = sizeof(chk<T>(0)) == sizeof(yes);     \
    }
HAS_MEM_FUNC(_to_integral, has_to_integral);

//****************************************************************************
//Anything with int _to_integral() (+ _from_integral(), i.e. any BetterEnum
//****************************************************************************
template<typename T >
struct json_traits<T, typename std::enable_if<has_to_integral<T, int(T::*)() const>::value>::type >
{
	static void append(buffer &json, const char *key, const T &value)
	{
		util::json_builder::append_integer(json, key, value._to_integral());
	}
	
	static void append(buffer &json, const T &value)
	{
		util::json_builder::append_integer(json, value._to_integral());
	}
};

template<typename T >
struct json_traits<T&, typename std::enable_if<has_to_integral<T, int(T::*)() const>::value>::type > :
public json_traits_int_common<T, long, INT_MAX_DIGITS, json_traits<T&>>
{
    static const char* type_out_of_range() { return "Int out of range"; }
    static const char* invalid_value_msg() { return "Invalid int value for key: "; }
    static long str_to_int(const char* str) { return std::strtol(str, nullptr, 10); }
    static T int_to_value(long l) { return T::_from_integral(l); }
};


//****************************************************************************
//Any enum
//****************************************************************************
template<typename T >
struct json_traits<T, typename std::enable_if<std::is_enum<T>::value>::type >
{
	static void append(buffer &json, const char *key, const T &value)
	{
		util::json_builder::append_integer(json, key, (int)value);
	}
	
	static void append(buffer &json, const T &value)
	{
		util::json_builder::append_integer(json, (int)value);
	}
};

template<typename T >
struct json_traits<T&, typename std::enable_if<std::is_enum<T>::value>::type > :
public json_traits_int_common<T, long, INT_MAX_DIGITS, json_traits<T&>>
{
    static const char* type_out_of_range() { return "Int out of range"; }
    static const char* invalid_value_msg() { return "Invalid int value for key: "; }
    static long str_to_int(const char* str) { return std::strtol(str, nullptr, 10); }
    static T int_to_value(long l) { return (T)l; }
};



//**************************************************************
//****************** ALL INTEGRAL TYPES ************************
//**************************************************************
/**
 We can simply specialize this with one definition here to cover any integral types (int, unsigned
 int, long, long long, etc)
 */
template<typename T>
struct json_traits<T, typename std::enable_if<std::is_integral<T>::value>::type>
{
    
    static void append(buffer &json, const char *key, const T &value)
    {
        util::json_builder::append_integer(json, key, value);
    }
    
    static void append(buffer &json, const T &value)
    {
        util::json_builder::append_integer(json, value);
    }
};


//**************************************************************
//*********************** INT **********************************
//**************************************************************
/**
 *  int type traits specialization
 */
template<>
struct json_traits<int&, void> :
public json_traits_int_common<int, long, INT_MAX_DIGITS, json_traits<int&>>
{
    static const char* type_out_of_range() { return "Int out of range"; }
    static const char* invalid_value_msg() { return "Invalid int value for key: "; }
    static long str_to_int(const char* str) { return std::strtol(str, nullptr, 10); }
    static int int_to_value(long l) { return (int)l; }
};

//**************************************************************
//*********************** UNSIGNED INT *************************
//**************************************************************
/**
 *  unsigned int type traits specialization
 */
template<>
struct json_traits<unsigned int&, void> :
public json_traits_int_common<unsigned int, unsigned long, UINT_MAX_DIGITS, json_traits<unsigned int&>>
{
    static const char* type_out_of_range() { return "Unsigned int out of range"; }
    static const char* invalid_value_msg() { return "Invalid unsigned int value for key: "; }
    static unsigned long str_to_int(const char* str) { return std::strtoul(str, nullptr, 10); }
    static unsigned int int_to_value(unsigned long l) { return (unsigned int)l; }
};

//**************************************************************
//*********************** LONG *********************************
//**************************************************************
/**
 *  long type traits specialization
 */
template<>
struct json_traits<long&, void> :
public json_traits_int_common<long, long, LONG_MAX_DIGITS, json_traits<long&>>
{
    static const char* type_out_of_range() { return "Long out of range"; }
    static const char* invalid_value_msg() { return "Invalid long value for key: "; }
    static long str_to_int(const char* str) { return std::strtol(str, nullptr, 10); }
    static long int_to_value(long l) { return l; }
};

//**************************************************************
//*********************** UNSIGNED LONG ************************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<unsigned long&, void> :
public json_traits_int_common<unsigned long, unsigned long, ULONG_MAX_DIGITS, json_traits<unsigned long&>>
{
    static const char* type_out_of_range() { return "Unsigned long out of range"; }
    static const char* invalid_value_msg() { return "Invalid unsigned long value for key: "; }
    static unsigned long str_to_int(const char* str) { return std::strtoul(str, nullptr, 10); }
    static unsigned long int_to_value(unsigned long l) { return l; }
};


//**************************************************************
//*********************** LONG LONG ***************************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<long long&, void> :
public json_traits_int_common<long long,long long, LONGLONG_MAX_DIGITS, json_traits<long long&>>
{
    static const char* type_out_of_range() { return "Long long out of range"; }
    static const char* invalid_value_msg() { return "Invalid long long value for key: "; }
    static unsigned long str_to_int(const char* str) {
#ifdef _MSC_VER
        return _strtoi64(str, nullptr, 10);
#else
        return std::strtoll(str, nullptr, 10);
#endif
    }
    static unsigned long int_to_value(unsigned long l) { return l; }
};

//**************************************************************
//*********************** UNSIGNED LONG LONG *******************
//**************************************************************
/**
 *  unsigned long type traits specialization
 */
template<>
struct json_traits<unsigned long long&, void> :
public json_traits_int_common<unsigned long long,unsigned long long, ULONGLONG_MAX_DIGITS, json_traits<unsigned long long&>>
{
    static const char* type_out_of_range() { return "Long long out of range"; }
    static const char* invalid_value_msg() { return "Invalid long long value for key: "; }
    static unsigned long long str_to_int(const char* str) {
#ifdef _MSC_VER
        return _strtoui64(str, nullptr, 10);
#else
        return std::strtoull(str, nullptr, 10);
#endif
    }
    static unsigned long long int_to_value(unsigned long long l) { return l; }
};


JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_INTEGERS_HPP

