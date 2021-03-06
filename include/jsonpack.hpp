/**
 *  Jsonpack - Library header
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

#ifndef JSONPACK_HPP
#define JSONPACK_HPP

#include "jsonpack/parser.hpp"
#include "jsonpack/exceptions.hpp"
#include "jsonpack/config.hpp"

#ifdef JSONPACK_USE_VARIADIC_TEMPLATES
#include "jsonpack/serializer/serializer_cpp11.hpp"
#else
#include "jsonpack/serializer/serializer_cpp03.h"
#endif


#ifndef WIN32
#define JSONPACK_EXPORT_DIRECTIVE
#else
#ifdef JSONPACK_EXPORT
#define JSONPACK_EXPORT_DIRECTIVE __declspec(dllexport)
#else
#define JSONPACK_EXPORT_DIRECTIVE __declspec(dllimport)
#endif
#endif

#define DEFINE_JSON_ATTRIBUTES(...)                                     \
    public:                                                             \
    char* json_pack(const bool &pretty = false, const unsigned &indent = 1, unsigned level = 0 )\
    {                                                                   \
        std::string _keys = jsonpack::util::str::trim( std::string(#__VA_ARGS__) );\
        jsonpack::buffer json;                                          \
        json.append( "{" , 1);                                          \
        if(pretty){ ++level; }\
        jsonpack::make_json(pretty, indent, level, json, _keys ,__VA_ARGS__);                  \
        return json.release();                                          \
    }                                                                   \
    void json_unpack(const char* json, const std::size_t &len)          \
    {                                                                   \
        jsonpack::object_t _members;                         \
        jsonpack::parser p;												\
         if(p.json_validate(json, len, _members))       				\
         {                                                              \
            std::string _keys = jsonpack::util::str::trim( std::string(#__VA_ARGS__) );\
            jsonpack::make_object(_members, const_cast<char*>(json), _keys, __VA_ARGS__);\
        }else{throw jsonpack::invalid_json(p.err_msg().c_str());}  		\
    }                                                                   \
    void json_unpack(const jsonpack::object_t &json, char* json_ptr)    \
    {                                                                   \
        std::string _keys = jsonpack::util::str::trim( std::string(#__VA_ARGS__) );\
        jsonpack::make_object(json, json_ptr, _keys, __VA_ARGS__);      \
    }


JSONPACK_API_BEGIN_NAMESPACE


////============================== SEQUENCES ==============================================

/**
 * Tempate function to serialize arrays from standard sequences
 * Allowed sequences:
 * array, vector, deque, list, forward_list, set, multiset, unordered_set, unordered_multiset
 */
template<typename Seq>
inline char* json_pack_sequence(const Seq& seq,
                                const bool&pretty = false, const unsigned& indent = 1, unsigned level = 0)
{
    jsonpack::buffer json;
    type::json_traits< Seq >::append(json, seq, pretty, indent, level);
    json.erase_last_comma();

    return json.release();
}

/**
 * Tempate function to deserialize arrays into standard sequences
 * Allowed sequences:
 * array, vector, deque, list, forward_list, set, multiset, unordered_set, unordered_multiset
 */
template<typename Seq>
inline void json_unpack_sequence(const char* json, const std::size_t &len, Seq& seq)
{
    array_t *arr = new array_t();

    parser p;
    if(p.json_validate(json, len, *arr))
    {
        value v(arr);

        type::json_extract_traits< Seq&, void >::extract(v, const_cast<char*>(json), seq);
    }
    else
    {
        throw jsonpack::invalid_json(p.err_msg().c_str());
    }
}


////============================== MAPS ==============================================

/**
 * Tempate function to serialize arrays from standard associative containers
 * Allowed containers:
 * map, multimap, unordered_map, unoredered_multimap
 */
template<typename Map>
inline char* json_pack_map(const Map& map,
                                const bool&pretty = false, const unsigned& indent = 1, unsigned level = 0)
{
    jsonpack::buffer json;
    type::json_traits< Map >::append(json, map, pretty, indent, level);
    json.erase_last_comma();

    return json.release();
}

/**
 * Tempate function to deserialize arrays into standard sequences
 * Allowed sequences:
 * array, vector, deque, list, forward_list, set, multiset, unordered_set, unordered_multiset
 */
template<typename Map>
inline void json_unpack_map(const char* json, const std::size_t &len, Map& map)
{
    object_t *obj = new object_t();

    parser p;
    if(p.json_validate(json, len, *obj))
    {
        value v(obj);

        type::json_extract_traits< Map&, void >::extract(v, const_cast<char*>(json), map);
    }
    else
    {
        throw jsonpack::invalid_json(p.err_msg().c_str());
    }
}


JSONPACK_API_END_NAMESPACE //jsonpack namespace



#endif // JSONPACK_HPP
