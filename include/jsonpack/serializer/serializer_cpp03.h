/**
 *  Jsonpack - Serialize and deserialize routines for c++03 standard
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

#ifndef JSONPACK_SERIALIZER_CPP03_H
#define JSONPACK_SERIALIZER_CPP03_H

#include "jsonpack/types.hpp"

JSONPACK_API_BEGIN_NAMESPACE


////============================== MAKE_JSON ==============================================
// 1 parameter
template <typename T>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v)
{
    register std::string::size_type pos = keys.find(',');

    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    json.erase_last_comma();
    json.append("}\0", 2);
}

// 2 parameters
template <typename T, typename T1>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1);
}

// 3 parameters
template <typename T, typename T1, typename T2>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2);
}
// 4 parameters
template <typename T, typename T1, typename T2, typename T3>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3);
}
// 5 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4);
}
// 6 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5);
}
// 7 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6);
}
// 8 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7);
}
// 9 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7, const T8& v8)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8);
}
// 10 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9);
}
// 11 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10);
}
// 12 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11);
}
// 13 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12);
}
// 14 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13);
}
// 15 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14);
}
// 16 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15);
}
// 17 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15, typename T16>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15, const T16& v16)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16);
}
// 18 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16, v17);
}
// 19 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18);
}
// 20 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19);
}
// 21 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20);
}
// 22 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21);
}
// 23 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22);
}
// 24 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23);
}
// 25 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24);
}
// 26 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25);
}
// 27 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26);
}
// 28 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26, const T27& v27)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26, v27);
}
// 29 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26, const T27& v27, const T28& v28)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26, v27, v28);
}
// 30 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26, const T27& v27, const T28& v28, const T29& v29)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26, v27, v28, v29);
}
// 31 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26, const T27& v27, const T28& v28, const T29& v29, const T30& v30)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26, v27, v28, v29, v30);
}
// 32 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
static inline void make_json(buffer &json, const std::string &keys,
                             const T& v, const T1& v1, const T2& v2, const T3& v3, const T4& v4, const T5& v5, const T6& v6, const T7& v7,
                             const T8& v8, const T9& v9, const T10& v10, const T11& v11, const T12& v12, const T13& v13, const T14& v14, const T15& v15,
                             const T16& v16, const T17& v17, const T18& v18, const T19& v19, const T20& v20, const T21& v21, const T22& v22, const T23& v23,
                             const T24& v24, const T25& v25, const T26& v26, const T27& v27, const T28& v28, const T29& v29, const T30& v30, const T31& v31)
{
    register std::string::size_type pos = keys.find(',');
    type::json_traits<T>::append(json, keys.substr(0, pos).c_str() , v);

    make_json(json, keys.substr(pos+1, keys.length()-1 ).c_str() ,
              v1, v2, v3, v4, v5, v6, v7, v8,
              v9, v10, v11, v12, v13, v14, v15, v16,
              v17, v18, v19, v20, v21, v22, v23, v24,
              v25, v26, v27, v28, v29, v30, v31);
}
////============================== MAKE_OBJECT ==============================================
// 1 parameter
template <typename T>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);

    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);
}

// 2 parameters
template <typename T, typename T1>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1);
}

// 3 parameters
template <typename T, typename T1, typename T2>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2);
}

// 4 parameters
template <typename T, typename T1, typename T2, typename T3>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3);
}

// 5 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4);
}

// 6 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5);
}

// 7 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6);
}

// 8 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7);
}

// 9 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8);
}

// 10 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9);
}

// 11 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10);
}

// 12 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11);
}

// 13 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12);
}

// 14 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13);
}

// 15 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14);
}

// 16 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15);
}

// 17 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16);
}

// 18 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17);
}

// 19 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18);
}

// 20 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19);
}

// 21 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20);
}

// 22 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21);
}

// 23 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22);
}

// 24 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23);
}

// 25 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24);
}

// 26 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24,T25 &v25)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25);
}

// 27 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24,T25 &v25,T26 &v26)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26);
}

// 28 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24,T25 &v25,T26 &v26,T27 &v27)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26, v27);
}

// 29 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24, T25 &v25, T26 &v26, T27 &v27, T28 &v28)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26, v27, v28);
}

// 30 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24, T25 &v25, T26 &v26, T27 &v27, T28 &v28, T29 &v29)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26, v27, v28, v29);
}

// 31 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24, T25 &v25, T26 &v26, T27 &v27, T28 &v28, T29 &v29, T30 &v30)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26, v27, v28, v29, v30);
}

// 32 parameters
template <typename T, typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7,
          typename T8, typename T9, typename T10, typename T11, typename T12, typename T13, typename T14, typename T15,
          typename T16, typename T17, typename T18, typename T19, typename T20, typename T21, typename T22, typename T23,
          typename T24, typename T25, typename T26, typename T27, typename T28, typename T29, typename T30, typename T31>
static inline void make_object(const object_t &json_obj, char* json_ptr, const std::string &keys,
                               T &v, T1 &v1, T2 &v2, T3 &v3, T4 &v4, T5 &v5, T6 &v6, T7 &v7,
                               T8 &v8, T9 &v9, T10 &v10, T11 &v11, T12 &v12, T13 &v13, T14 &v14, T15 &v15,
                               T16 &v16, T17 &v17, T18 &v18, T19 &v19, T20 &v20, T21 &v21, T22 &v22, T23 &v23,
                               T24 &v24, T25 &v25, T26 &v26, T27 &v27, T28 &v28, T29 &v29, T30 &v30, T31 &v31)
{
    register std::string::size_type pos = keys.find(',');
    std::string current_key = keys.substr(0, pos);
    type::json_extract_traits<T&>::extract(json_obj, json_ptr, current_key.c_str(), current_key.length(), v);

    make_object(json_obj, json_ptr, keys.substr(pos+1, keys.length()-1 ).c_str(),
                v1, v2, v3, v4, v5, v6, v7, v8,
                v9, v10, v11, v12, v13, v14, v15, v16,
                v17, v18, v19, v20, v21, v22, v23, v24,
                v25, v26, v27, v28, v29, v30, v31);
}
JSONPACK_API_END_NAMESPACE //jsonpack namespace


#endif // JSONPACK_SERIALIZER_CPP03_H

