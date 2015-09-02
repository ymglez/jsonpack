/**
 *  Jsonpack - Type traits for json operations
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

#ifndef JSONPACK_TYPE_TRAITS_BASE_HPP
#define JSONPACK_TYPE_TRAITS_BASE_HPP
#
#include "jsonpack/util/builder.hpp"
#include "jsonpack/object.hpp"


/**
 * Disable unused attribute warnings
 */
#ifdef __GNUC__
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_## x
#endif


JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

/**
 * Type traits base for json operations
 * specialization for object types
 */
template<typename T>
struct json_traits
{
    /**
     * Add the object in json buffer like "key": {value},
     */
    static void append(buffer &json, const char *key, const T &value)
    {
        util::json_builder::append_string(json, key, const_cast<T&>(value).json_pack() );
    }

    /**
     * Add the object in json buffer like {value},
     */
    static void append(buffer &json, const T &value)
    {
        char* str = const_cast<T&>(value).json_pack();
        json.append(str, strlen(str));
        json.append(",", 1);
    }
};

template<typename T>
struct json_traits<T&>
{
    /**
     * Searches for the given key and obtain the associated jsonpack::value
     */
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, T &value)
    {
        jsonpack::key k;
        k._bytes = len;
        k._ptr = key;

        object_t::const_iterator found = json.find(k);
        if( found != json.end() )  // exist the current key
        {
            //Accept object or null
            if(found->second._field == _OBJ ||
                    ( found->second._field == _POS && found->second._pos._type == JTK_NULL ) )
            {
                extract(found->second, json_ptr, value);
            }
            else
            {
                std::string msg = "Invalid object value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    /**
     * Get the jsonpack::value as object type
     */
    static void extract(const jsonpack::value &v, char* json_ptr, T &value)
    {
        //if not null do something
        if( v._field != _POS )
        {
            value.json_unpack( *v._obj , json_ptr ) ;
        }
    }
};

JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_TYPE_TRAITS_BASE_HPP

