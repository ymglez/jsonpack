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

#include <map>
#include <vector>
#include <unordered_map>
#include <string.h>

#include "jsonpack/util/builder.hpp"
#include "jsonpack/exceptions.hpp"
#include "jsonpack/parser.hpp"

//#include "jsonpack/vector.hpp"
//#include "jsonpack/umap.hpp"

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
 * Represent a keys in the json string
 */
struct key
{
    bool operator== (const key &k1) const
    {
        std::size_t min =  std::min( k1._bytes, _bytes );
        bool ret = ( memcmp(k1._ptr, _ptr, min) == 0 );
        return ret;
    }

    /**
     * Less operator required for container
     */
    bool operator < (const key &UNUSED(other)) const
    { return true; } //order doesnt matter

    key():_ptr(nullptr), _bytes(0){}

    key(const key& k):
        _ptr(k._ptr),
        _bytes(k._bytes)
    {}

#ifndef _MSC_VER
    const char * _ptr = nullptr;
    std::size_t _bytes = 0;
#else
    const char * _ptr;
    std::size_t _bytes;
#endif
};

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

    JTK_INVALID = 12,
	JTK_EOF
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
typedef std::unordered_map<key, value, key_hash >  object_t;

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
    /**
     * Constructors
     */
    value() :_field(_NULL),_p(),_obj_ptr_count(0),_arr_ptr_count(0)
    {}

    value(position p) :_field(_POS),_p(),_obj_ptr_count(0),_arr_ptr_count(0)
    { _pos = p; }

    value(object_t* o) :_field(_OBJ),_p(),_obj_ptr_count(1),_arr_ptr_count(0)
    { _obj = o;}

    value(array_t* a) :_field(_ARR),_p(),_obj_ptr_count(0),_arr_ptr_count(1)
    { _arr = a;}

    value (const value &rv):_field(_NULL),_p(),_obj_ptr_count(0),_arr_ptr_count(0)
    {
        cleanup();

        switch (rv._field)
        {
        case _POS:
            _pos = rv._pos;
            break;
        case _ARR:
            _arr = rv._arr;
            _arr_ptr_count = rv._arr_ptr_count;
            rv._arr_ptr_count++;
            break;
        case _OBJ:
            _obj = rv._obj;
            _obj_ptr_count = rv._obj_ptr_count;
            rv._obj_ptr_count++;
        default:
            break;
        }

        _field = rv._field;
    }

    /**
     * Assignment operators
     */
    value& operator =(object_t* o)
    {
        cleanup();
        _field = _OBJ;
        _obj = o;
        _obj_ptr_count++;


        return *this;
    }

    value& operator =(array_t* a)
    {
        cleanup();
        _field = _ARR;
        _arr = a;
        _arr_ptr_count++;

        return *this;
    }

    value& operator =(value &rv)
    {
        cleanup();

        switch (rv._field)
        {
        case _POS:
            _pos = rv._pos;
            break;
        case _ARR:
            _arr = rv._arr;
            _arr_ptr_count = rv._arr_ptr_count;
            rv._arr_ptr_count++;
            break;
        case _OBJ:
            _obj = rv._obj;
            _obj_ptr_count = rv._obj_ptr_count;
            rv._obj_ptr_count++;
        default:
            break;
        }
        _field = rv._field;

        return *this;
    }

    /**
     * Destructor
     */
    ~value()
    {
        switch (_field)
        {
        case _ARR:
            if(--_arr_ptr_count == 0) //i am the last owner
            {
                delete _arr;
                _arr = nullptr;
            }
            break;
        case _OBJ:
            if(--_obj_ptr_count == 0)
            {
                delete _obj;
                _obj = nullptr;
            }
        default:
            break;
        }
    }

    void cleanup()
    {
        //clean up before
        if(is_object())
        {
            delete _obj;
            _obj = nullptr;
        }
        else if(is_array())
        {
            delete _arr;
            _arr = nullptr;
        }
    }

    /**
     * Type check
     */
    bool is_null()
    { return (_field == _NULL || (_field == _POS && _pos._type == JTK_NULL ) ); }

    bool is_boolean()
    { return (_field == _POS && ( _pos._type == JTK_TRUE || _pos._type == JTK_FALSE ) ); }

    bool is_integer()
    { return (_field == _POS && _pos._type == JTK_INTEGER ); }

    bool is_real()
    { return (_field == _POS && _pos._type == JTK_REAL ); }

    bool is_string()
    { return (_field == _POS && _pos._type == JTK_STRING_LITERAL ); }

    bool is_object()
    { return (_field == _OBJ); }

    bool is_array()
    { return (_field == _ARR); }

    /**
     * Explicit type conversion between current JSON value
     * and a compatible non-pointer type.
     */
    template<typename T>
    T get(typename
          std::enable_if<
          ! std::is_pointer<T>::value
          ,int>::type* = nullptr ) const
    {
        T  _val;
        type::json_traits<T&>::extract(*this, nullptr, _val);
        return _val;
    }


    /**
     * Explicit type conversion between the current json value
     * and the given reference
     */
    template<typename T >
    void operator()(T& _val, typename
                    std::enable_if<
                    ! std::is_pointer<T>::value
                    ,int>::type* = nullptr)
    {
        if(_field == _POS && !type::json_traits<T&>::match_token_type(*this) )
            throw type_error("Types mismatch");

        type::json_traits<T&>::extract(*this, nullptr, _val);
    }

    std::size_t size() const
    {
        if(_field == _ARR)
            return _arr->size();
        else if(_field == _OBJ)
            return _obj->size();

        throw type_error("size must be used with array or object");
    }



    /**
     * Lookup when json value is
     * OBJECT
     */
    value& operator[](const std::string &__str_key)
    {
        if(_field != _OBJ) throw type_error("current value is not an object!");

        key obj_key;
        obj_key._ptr = __str_key.c_str();
        obj_key._bytes = __str_key.length();

        return _obj->operator [](obj_key);
    }

    std::vector<std::string> members()
    {
        if(_field != _OBJ) throw type_error("current value is not an object!");

        std::vector<std::string> m(_obj->size());

        for(object_t::iterator pair  = _obj->begin(); pair != _obj->end(); pair++)
            m.emplace_back( pair->first._ptr, pair->first._bytes);

        return m;
    }

    /**
     * Vector operations when json value is
     * ARRAY
     */
    value& operator[](const std::size_t __index)
    {
        if(_field != _ARR) throw type_error("current value is not an array!");
        return _arr->operator [](__index);
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

    /**
     * Create a json from value
     */
    //    void append(buffer &json)
    //    {
    //        if( is_array() )
    //            _arr->append(json);
    //        else if(is_object())
    //            _obj->append(json);
    //        else if( is_string() )
    //                util::json_builder::append_string(json, _pos._pos, _pos._count);
    //        else
    //        {
    //            json.append(_pos._pos, _pos._count);
    //            json.append(",", 1);
    //        }
    //    }

    void json_unpack(const char* json, const std::size_t &len)
    {
        cleanup();

        if(*json == '[')
        {
            _field = _ARR;
            _arr = new array_t();
            _arr_ptr_count = 1;


            if(!_p.json_validate(json, len, *_arr))
                throw invalid_json( _p.err_msg().c_str() );
        }
        else if(*json == '{')
        {
            _field = _OBJ;
            _obj = new object_t();
            _obj_ptr_count = 1;

            if(!_p.json_validate(json, len, *_obj))
                throw invalid_json( _p.err_msg().c_str() );
        }
        else
            throw invalid_json("JSON must be object or array");
    }

    fields _field;

    union
    {
        position   _pos;
        object_t*  _obj;
        array_t*   _arr;
    };

    parser _p;
    mutable unsigned _obj_ptr_count;
    mutable unsigned _arr_ptr_count;
};



JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_ARRAY_OBJECT_HPP

