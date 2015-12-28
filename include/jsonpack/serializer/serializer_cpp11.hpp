/**
 *  Jsonpack - Serialize and deserialize routines for c++11 standard
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

#ifndef JSONPACK_SERIALIZER_CPP11_HPP
#define JSONPACK_SERIALIZER_CPP11_HPP

#include "jsonpack/types.hpp"

JSONPACK_API_BEGIN_NAMESPACE


////============================== MAKE_JSON ==============================================

static inline void make_json(buffer &json, const std::string &UNUSED(key) )
{
    json.erase_last_comma();
    json.append("}\0", 2);
}

template <typename T, typename ...Types >
static inline void make_json(buffer &json, const std::string &keys, const T& val, const Types& ...values )
{
    std::string::size_type pos = keys.find(',');

    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , val);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,values...);
}

////============================== MAKE_OBJECT ==============================================
static inline void make_object(const object_t &UNUSED(json), char* UNUSED(json_ptr), const std::string &UNUSED(key) )
{
}

template <typename T, typename ...Types >
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys, T &val, Types& ...values )
{
    std::string::size_type pos = keys.find(',');

    std::string current_key = keys.substr(0, pos);

    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), val);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(), values...);
}

JSONPACK_API_END_NAMESPACE //jsonpack namespace

#endif // JSONPACK_SERIALIZER_CPP11_HPP

