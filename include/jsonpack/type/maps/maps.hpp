/**
 *  Jsonpack - Maps traits for json operations
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

#ifndef JSONPACK_MAPS_HPP
#define JSONPACK_MAPS_HPP

#include "jsonpack/type/simple_type.hpp"

JSONPACK_API_BEGIN_NAMESPACE
TYPE_BEGIN_NAMESPACE

/**
 *  Generic standard associative container traits specialization
 *  Allowed associative container:
 *  map, multimap, unordered_map, unordered_multimap
 */
template<typename Map>
struct map_traits
{
    typedef typename Map::mapped_type type_t;

    //"name":{"key0":value0, "key1":value1, "key2":value2}
    static void append(buffer &json, const char *key, const Map &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        json.append("\"", 1);
        json.append(key, strlen(key) );
        json.append("\":", 2);

        append(json, value, pretty, indent, level);
    }

    static void append(buffer &json, const Map &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        json.append("{", 1);

        if(pretty)
            ++level;

        for(const auto &v : value)
        {
            if(pretty)
            {
                json.append("\n",1);
                json.append(' ', indent * level);
            }

//            json.append("{",1);
            json_traits<type_t, void>::append(json, v.first.c_str(), v.second , pretty, indent, level);
//            json.erase_last_comma();
//            json.append("},",2);
        }

        json.erase_last_comma();

        if (pretty)
        {
            --level;
            json.append("\n", 1);
            json.append(' ', indent * level);
        }

        json.append("},", 2);
    }

};

template<typename Map>
struct map_traits<Map&>
{
    typedef typename Map::mapped_type type_t;

    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, Map &value)
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
                std::string msg = "Invalid map value for key: ";
                msg += key;
                throw type_error( msg.data() );
            }
        }
    }

    static void extract(const jsonpack::value &v, char* json_ptr, Map &value)
    {
        object_t map = *v._obj;
        value.clear();

        for(const auto & pair : map)
        {
#ifndef _MSC_VER
            // Initialize before use
            std::string name;
            name.reserve(pair.first._bytes + 1);
            name.resize(pair.first._bytes);

            type_t second = {};
#else
            key_t first;
            type_t second;
#endif

            memcpy(const_cast<char*>(name.data()), pair.first._ptr, pair.first._bytes);

            json_extract_traits<type_t&,void>::extract(pair.second, json_ptr, second);
            value.insert(value.end(), std::make_pair(name, second));
        }
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return v.is_object();
    }
};

/** **********************************************************************
 * ****************** map type traits specialization *********************
 *************************************************************************/
template<typename T>
struct json_traits<std::map<std::string,T> >
{
    static void append(buffer &json, const char *key, const std::map<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::map<std::string,T>>::append(json, key, value, pretty, indent, level);
    }

    static void append(buffer &json, const std::map<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::map<std::string,T>>::append(json, value, pretty, indent, level);
    }
};

template<typename T>
struct json_extract_traits<std::map<std::string,T>&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::map<std::string,T> &value)
    {
        map_traits<std::map<std::string,T>&>::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::map<std::string,T> &value)
    {
        map_traits<std::map<std::string,T>&>::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return v.is_object();
    }
};

/** **********************************************************************
 * ****************** multimap type traits specialization ****************
 *************************************************************************/
template<typename T>
struct json_traits<std::multimap<std::string,T> >
{
    static void append(buffer &json, const char *key, const std::multimap<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::multimap<std::string,T>>::append(json, key, value, pretty, indent, level);
    }

    static void append(buffer &json, const std::multimap<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::multimap<std::string,T>>::append(json, value, pretty, indent, level);
    }
};

template<typename T>
struct json_extract_traits<std::multimap<std::string,T>&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::multimap<std::string,T> &value)
    {
        map_traits<std::multimap<std::string,T>&>::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::multimap<std::string,T> &value)
    {
        map_traits<std::multimap<std::string,T>&>::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return v.is_object();
    }
};

/** **********************************************************************
 * *********** unordered_map type traits specialization ******************
 *************************************************************************/
template<typename T>
struct json_traits<std::unordered_map<std::string,T> >
{
    static void append(buffer &json, const char *key, const std::unordered_map<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::unordered_map<std::string,T>>::append(json, key, value, pretty, indent, level);
    }

    static void append(buffer &json, const std::unordered_map<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::unordered_map<std::string,T>>::append(json, value, pretty, indent, level);
    }
};

template<typename T>
struct json_extract_traits<std::unordered_map<std::string,T>&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::unordered_map<std::string,T> &value)
    {
        map_traits<std::unordered_map<std::string,T>&>::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::unordered_map<std::string,T> &value)
    {
        map_traits<std::unordered_map<std::string,T>&>::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return v.is_object();
    }
};

/** **********************************************************************
 * ****************** map type traits specialization *********************
 *************************************************************************/
template<typename T>
struct json_traits<std::unordered_multimap<std::string,T> >
{
    static void append(buffer &json, const char *key, const std::unordered_multimap<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::unordered_multimap<std::string,T>>::append(json, key, value, pretty, indent, level);
    }

    static void append(buffer &json, const std::unordered_multimap<std::string,T> &value,
                       const bool&pretty, const unsigned& indent, unsigned& level)
    {
        map_traits<std::unordered_multimap<std::string,T>>::append(json, value, pretty, indent, level);
    }
};

template<typename T>
struct json_extract_traits<std::unordered_multimap<std::string,T>&, void>
{
    static void extract(const object_t &json, char* json_ptr, const char *key, const std::size_t &len, std::unordered_multimap<std::string,T> &value)
    {
        map_traits<std::unordered_multimap<std::string,T>&>::extract(json, json_ptr, key, len, value);
    }

    static void extract(const jsonpack::value &v, char* json_ptr, std::unordered_multimap<std::string,T> &value)
    {
        map_traits<std::unordered_multimap<std::string,T>&>::extract(v, json_ptr, value);
    }

    static bool match_token_type(const jsonpack::value &v)
    {
        return v.is_object();
    }
};

JSONPACK_API_END_NAMESPACE //type
JSONPACK_API_END_NAMESPACE //jsonpack

#endif // JSONPACK_MAPS_HPP

