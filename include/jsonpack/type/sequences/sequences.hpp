/**
 *  Jsonpack - Generic standard sequences traits for json operations
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

#ifndef JSONPACK_SEQUENCES_HPP
#define JSONPACK_SEQUENCES_HPP

#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>

#include "jsonpack/type/simple_type.hpp"

JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

/**
 *  Generic standard sequences traits specialization
 *  Allowed sequences:
 *  array, vector, deque, list, forward_list, set, multiset, unordered_set, unordered_multiset
 */
template<typename Seq>
struct sequence_traits
{
    typedef typename Seq::value_type type_t;

    static void append(buffer &json, const char *key, const Seq &value)
    {
        json.append("\"", 1);
        json.append(key, strlen(key) );
        json.append("\":[", 3);

        for(const auto &v : value)
        {
            json_traits<type_t>::append(json, v);
        }

        json.erase_last_comma();
        json.append("],", 2);
    }

    static void append(buffer &json, const Seq &value)
    {
        json.append("[", 1);

        for(const auto &v : value)
        {
            json_traits<type_t>::append(json, v);
        }
        json.erase_last_comma();
        json.append("],", 2);
    }

};

template<typename Seq>
struct sequence_traits<Seq&>
{
    typedef typename Seq::value_type type_t;

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, Seq &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            if(found->second._field == _ARR )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid array value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, Seq &value)
    {
        array_t arr = *v._arr;
        value.clear();

        for(const auto &it : arr)
        {
#ifndef _MSC_VER
            // Initialize before use
            type_t val = {};
#else
            type_t val;
#endif  
            if( json_traits<type_t&>::match_token_type(it) )
            {
                json_traits<type_t&>::extract(it, json_ptr, val);
                value.insert(value.end(), val); //faster way in each container
            }
            else
            {
                throw type_error( "Array item type mismatch" );
            }
        }
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::array type traits specialization **********************
 *************************************************************************/
template<typename T, std::size_t N >
struct json_traits< std::array<T,N> >
{
    static void append(buffer &json, const char *key, const std::array<T,N> &value)
    {
        sequence_traits< std::array<T,N> >::append(json, key, value);
    }

    static void append(buffer &json, const std::array<T,N> &value)
    {
        sequence_traits< std::array<T,N> >::append(json, value);
    }
};

template<typename T, std::size_t N >
struct json_traits<std::array<T,N>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::array<T,N> &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )    // exist the current key
        {
            if(found->second._field == _ARR )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid array value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    
    static void extract(const jsonpack::value &v, char* json_ptr, std::array<T,N> &value)
    {
        array_t arr = *v._arr;

        for(std::size_t i = 0 ; i < arr.size(); ++i)
        {
#ifndef _MSC_VER
            T val = {};
#else
            T val;
#endif  
            if( json_traits<T&>::match_token_type(arr[i]) )
            {
                json_traits<T&>::extract(arr[i], json_ptr, val);
                // array not support insert operation
                value[i] = val;
            }
            else
            {
                throw type_error( "Array item type mismatch" );
            }
        }
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};


/** **********************************************************************
 * *********** std::vector type traits specialization **********************
 *************************************************************************/
template<typename T>
struct json_traits< std::vector<T> >
{
    static void append(buffer &json, const char *key, const std::vector<T> &value)
    {
        sequence_traits< std::vector<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::vector<T> &value)
    {
        sequence_traits< std::vector<T> >::append(json, value);
    }

};

template<typename T>
struct json_traits<std::vector<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::vector<T> &value)
    {
        sequence_traits< std::vector<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::vector<T> &value)
    {
        sequence_traits< std::vector<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::deque type traits specialization **********************
 *************************************************************************/
template<typename T>
struct json_traits< std::deque<T> >
{
    static void append(buffer &json, const char *key, const std::deque<T> &value)
    {
        sequence_traits< std::deque<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::deque<T> &value)
    {
        sequence_traits< std::deque<T> >::append(json, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

template<typename T>
struct json_traits<std::deque<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::deque<T> &value)
    {
        sequence_traits< std::deque<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::deque<T> &value)
    {
        sequence_traits< std::deque<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::list type traits specialization **********************
 *************************************************************************/
template<typename T>
struct json_traits< std::list<T> >
{
    static void append(buffer &json, const char *key, const std::list<T> &value)
    {
        sequence_traits< std::list<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::list<T> &value)
    {
        sequence_traits< std::list<T> >::append(json, value);
    }
};

template<typename T>
struct json_traits<std::list<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::list<T> &value)
    {
        sequence_traits< std::list<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::list<T> &value)
    {
        sequence_traits< std::list<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::forward_list type traits specialization **********************
 *************************************************************************/
template<typename T>
struct json_traits< std::forward_list<T> >
{
    static void append(buffer &json, const char *key, const std::forward_list<T> &value)
    {
        sequence_traits< std::forward_list<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::forward_list<T> &value)
    {
        sequence_traits< std::forward_list<T> >::append(json, value);
    }
};

// get elements in inverse order
template<typename T>
struct json_traits<std::forward_list<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::forward_list<T> &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )
        {
            if(found->second._field == _ARR )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid array value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::forward_list<T> &value)
    {
        array_t arr = *v._arr;

        value.clear();

        for(const auto &it : arr)
        {
#ifndef _MSC_VER
            // Initialize before use
            T val = {};
#else
            T val;
#endif  
            if( json_traits<T&>::match_token_type(it) )
            {
                json_traits<T&>::extract(it, json_ptr, val);
                // forward_list not support insert operation
                value.push_front(val);
            }
            else
            {
                throw type_error( "Forward_list item type mismatch" );
            }
        }
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::set type traits specialization **********************
 *************************************************************************/
template<typename T>
struct json_traits< std::set<T> >
{
    static void append(buffer &json, const char *key, const std::set<T> &value)
    {
        sequence_traits< std::set<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::set<T> &value)
    {
        sequence_traits< std::set<T> >::append(json, value);
    }
};

template<typename T>
struct json_traits<std::set<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::set<T> &value)
    {
        sequence_traits< std::set<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::set<T> &value)
    {
        sequence_traits< std::set<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::multiset type traits specialization ******************
 *************************************************************************/
template<typename T>
struct json_traits< std::multiset<T> >
{
    static void append(buffer &json, const char *key, const std::multiset<T> &value)
    {
        sequence_traits< std::multiset<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::multiset<T> &value)
    {
        sequence_traits< std::multiset<T> >::append(json, value);
    }
};

template<typename T>
struct json_traits<std::multiset<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::multiset<T> &value)
    {
        sequence_traits< std::multiset<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::multiset<T> &value)
    {
        sequence_traits< std::multiset<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::unordered_set type traits specialization *************
 *************************************************************************/
template<typename T>
struct json_traits< std::unordered_set<T> >
{
    static void append(buffer &json, const char *key, const std::unordered_set<T> &value)
    {
        sequence_traits< std::unordered_set<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::unordered_set<T> &value)
    {
        sequence_traits< std::unordered_set<T> >::append(json, value);
    }
};

template<typename T>
struct json_traits<std::unordered_set<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::unordered_set<T> &value)
    {
        sequence_traits< std::unordered_set<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::unordered_set<T> &value)
    {
        sequence_traits< std::unordered_set<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};

/** **********************************************************************
 * *********** std::unordered_multiset type traits specialization ********
 *************************************************************************/
template<typename T>
struct json_traits< std::unordered_multiset<T> >
{
    static void append(buffer &json, const char *key, const std::unordered_multiset<T> &value)
    {
        sequence_traits< std::unordered_multiset<T> >::append(json, key, value);
    }

    static void append(buffer &json, const std::unordered_multiset<T> &value)
    {
        sequence_traits< std::unordered_multiset<T> >::append(json, value);
    }
};

template<typename T>
struct json_traits<std::unordered_multiset<T>& >
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::unordered_multiset<T> &value)
    {
        sequence_traits< std::unordered_multiset<T>& >::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::unordered_multiset<T> &value)
    {
        sequence_traits< std::unordered_multiset<T>& >::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return (v._field == _ARR);
    }
};



JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_SEQUENCES_HPP
