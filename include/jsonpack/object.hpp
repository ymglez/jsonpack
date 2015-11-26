/**
 *  Jsonpack - JSON value representation
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

#ifndef JSONPACK_ARRAY_OBJECT_HPP
#define JSONPACK_ARRAY_OBJECT_HPP

#include <vector>
#include <string.h>

#include "jsonpack/umap.hpp"

JSONPACK_API_BEGIN_NAMESPACE

/**
 * hash function for non null-terminated byte strings
 * http://www.cse.yorku.ca/~oz/hash.html
 */
inline unsigned long _hash_bytes(const char* __str, const unsigned long & _bytes)
{
    unsigned long hash = 5381, count = _bytes;
    int c ;

    while (count--)
    {
        c = *__str++;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

/**
 * Functor to hash keys in unordered_map
 */
struct key_hash
{
    std::size_t operator()( key const &__val) const
    {
        return _hash_bytes(__val._ptr , __val._bytes);
    }
};

/**
 * JSON tokens
 */
enum jsonpack_token_type : unsigned
{
    JTK_OPEN_KEY = 0,
    JTK_CLOSE_KEY = 1,
    JTK_COLON = 2,
    JTK_COMMA = 3,
    JTK_OPEN_BRACKET = 4,
    JTK_CLOSE_BRACKET = 5,

    JTK_STRING_LITERAL = 6,

    JTK_INTEGER = 7,
    JTK_REAL = 8,

    JTK_TRUE = 9,
    JTK_FALSE = 10,
    JTK_NULL = 11,

    JTK_INVALID = 12
};

/**
 * Position of a value in string json
 */
struct position
{
    jsonpack_token_type _type;
    char* _pos;
    unsigned long _count;

#if !defined(_MSC_VER) && !defined(__APPLE__)
    position& operator =(const position &rvalue)
    {
        _type = rvalue._type;
        _pos = rvalue._pos;
        _count = rvalue._count;
        return *this;
    }
#endif
};

struct value;

/**
 * Collection of key/value pairs (javascript object)
 */
typedef jsonpack::umap<key, value, key_hash >  object_t;

/**
 * Sequence of values
 */
typedef std::vector<value> array_t;

/**
 * For union active field control
 */
enum fields
{
    _POS,
    _OBJ,
    _ARR,
    _NULL
};

TYPE_BEGIN_NAMESPACE
    template<typename T>
    struct json_traits;
JSONPACK_API_END_NAMESPACE //type

/**
 * Represent a JSON value. The union wrapper can represents a:
 * - position of: integer, real, UTF-8 string, boolean or null
 * - an array_t
 * - an object_t
 */
struct value
{
    explicit value():_field(_NULL){}

    fields _field;

    union
    {
        position   _pos;
        object_t*  _obj;
        array_t*   _arr;
    };

    value& operator =(const value &rv)
    {
        _field = rv._field;
        switch (_field)
        {
        case _POS:
            _pos = rv._pos;
            break;
        case _ARR:
            _arr = rv._arr;
            break;
        default:
            _obj = rv._obj;
            break;
        }

        return *this;
    }

    /**
     * Get the current json value into the given reference,
     * performing conversion
     */
    template<typename T>
    void operator()(T& _val)
    {
        if( !type::json_traits<T&>::match_token_type(*this) )
            throw type_error("Types mismatch");

        type::json_traits<T&>::extract(*this, nullptr, _val);
    }

    /**
     * Lookup when json value is an object
     */
    value operator[](const std::string &__str_key)
    {
        if(_field != _OBJ) throw type_error("current value is not an object!");
            return _obj->operator [](__str_key.c_str());
    }

    /**
     * Vector operations when json value is an array
     * throw exception if current value is not an array
     */
    value operator[](const std::size_t __index)
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->operator [](__index);
    }
    std::size_t size() const
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->size();
    }

    array_t::iterator begin()
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->begin();
    }

    array_t::const_iterator begin() const
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->begin();
    }

    array_t::iterator end()
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->end();
    }

    array_t::const_iterator end() const
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->end();
    }
};

//forward
static inline void delete_object(object_t *obj);

/**
 * Function to free array_t
 */
static inline void delete_array(array_t *arr)
{
    for(array_t::iterator elem = arr->begin(); elem != arr->end(); elem++)
    {
        if((*elem)._field == _OBJ)
        {
            delete_object((*elem)._obj);
        }
        else if((*elem)._field == _ARR)
        {
            delete_array((*elem)._arr);
        }
    }

    arr->clear();
    delete arr;
    arr = nullptr;
}

/**
 * Function to free object_t
 */
static inline void delete_object(object_t *obj)
{
    for(object_t::iterator it = obj->begin(); it != obj->end(); it++)
    {
        if(it->second._field == _OBJ)
        {
            delete_object(it->second._obj);
        }
        else if(it->second._field == _ARR)
        {
            delete_array(it->second._arr);
        }
    }

    obj->clear();
    delete obj;
    obj = nullptr;
}

/**
 * Function to free internal elements
 */
static inline void clean_object(object_t & obj)
{
    for(object_t::iterator it = obj.begin(); it != obj.end(); it++)
    {
        if(it->second._field == _OBJ)
        {
            delete_object(it->second._obj);
        }
        else if(it->second._field == _ARR)
        {
            delete_array(it->second._arr);
        }
    }
}


JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_ARRAY_OBJECT_HPP

