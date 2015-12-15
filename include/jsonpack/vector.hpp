/**
 *  Jsonpack - JSON array representation
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
#ifndef JSONPACK_VECTOR_HPP
#define JSONPACK_VECTOR_HPP

#include <vector>
#include <array>
#include <deque>
#include <list>
#include <forward_list>
#include <set>
#include <unordered_set>
#include <type_traits>

#include "jsonpack/parser.hpp"
#include "jsonpack/exceptions.hpp"
#include "jsonpack/config.hpp"

JSONPACK_API_BEGIN_NAMESPACE

TYPE_BEGIN_NAMESPACE
template<typename T>
struct json_traits;
JSONPACK_API_END_NAMESPACE //type

/**
 * std::vector adapter overloading operator[](const char*) for easy lookup,
 * added json_unpack() member for parsing json array
 */
template<typename _Tp>
class vector
{

public:
    typedef typename std::vector<_Tp>               base_vector;
    typedef _Tp                                     value_type;
    typedef typename base_vector::pointer           pointer;
    typedef typename base_vector::const_pointer     const_pointer;
    typedef typename base_vector::reference         reference;
    typedef typename base_vector::const_reference   const_reference;
    typedef typename base_vector::iterator          iterator;
    typedef typename base_vector::const_iterator    const_iterator;
    typedef size_t                                  size_type;

    bool _auto_clear;

private:
    base_vector _vect;
    jsonpack::parser _p;

public:
    vector(bool auto_clear = true):
        _auto_clear(auto_clear),
        _vect(),
        _p()
    {}

    ~vector()
    {
        if(_auto_clear)
            parser::clear(this);
    }

    iterator begin() noexcept
    { return _vect.begin(); }

    const_iterator begin() const noexcept
    { return _vect.begin(); }

    iterator end() noexcept
    { return _vect.end(); }

    const_iterator end() const noexcept
    { return _vect.end(); }

    size_type size() const noexcept
    { return _vect.size(); }

    reference operator[](size_type __n) noexcept
    { return _vect.operator [](__n);; }

    const_reference operator[](size_type __n) const noexcept
    { return _vect.operator [](__n); }

    void clear() noexcept
    { _vect.clear(); }

    void push_back(const value_type& __x)
    { _vect.push_back(__x);}

    /**
     * Parse json string into a jsonpack::object_t or jsonpack::array_t(this)
     */
    void json_unpack(const char* json, const std::size_t &len)
    {
        if(!_p.json_validate(json, len, *this))
			throw invalid_json( _p.err_msg().c_str() );
    }

    /**
     * Explicit type conversion between current JSON array
     * and a compatible non-pointer standard sequence containers
     */
    template< typename Seq>
    void operator()(Seq & seq)
    {
        seq = get<Seq>();
    }


    /**
     * Explicit type conversion between current JSON array
     * and a compatible non-pointer standard sequence containers:
     * vector, deque, list, set, multiset, unordered_set, unordered_multiset
     */
    template< typename Seq >
    Seq get(typename
            std::enable_if<
            std::is_same<std::vector<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::deque<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::list<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::set<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::multiset<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::unordered_set<typename Seq::value_type> ,Seq>::value ||
            std::is_same<std::unordered_multiset<typename Seq::value_type> ,Seq>::value
            ,int>::type* = nullptr) const
    {
        Seq  arr;
        typedef typename Seq::value_type type_t;
        for(const auto &it : *this)
        {
#ifndef _MSC_VER
            // Initialize before use
            type_t val = {};
#else
            type_t val;
#endif
            if( type::json_traits<type_t&>::match_token_type(it) )
            {
                type::json_traits<type_t&>::extract(it, nullptr, val);
                arr.insert(arr.end(), val);
            }
            else
            {
                throw type_error( "Array item type mismatch" );
            }
        }
        return arr;
    }

    /**
     * Explicit type conversion between current JSON array
     * and a compatible non-pointer standard sequence container: forward_list
     */
    template< typename FList >
    FList get(typename
              std::enable_if<
              std::is_same<std::forward_list<typename FList::value_type> ,FList>::value
              ,int>::type* = nullptr) const
    {
        FList  arr;
        typedef typename FList::value_type type_t;
        for(const auto &it : *this)
        {
#ifndef _MSC_VER
            // Initialize before use
            type_t val = {};
#else
            type_t val;
#endif
            if( type::json_traits<type_t&>::match_token_type(it) )
            {
                type::json_traits<type_t&>::extract(it, nullptr, val);
                arr.push_front(val);
            }
            else
            {
                throw type_error( "Array item type mismatch" );
            }
        }
        return arr;
    }

    /**
     * Explicit type conversion between current JSON array
     * and a compatible non-pointer standard sequence container: array
     */
    template< typename A >
    A get(typename
          std::enable_if<
          std::is_same<std::array<typename A::value_type, std::tuple_size<A>::value > ,A>::value
          ,int>::type* = nullptr) const
    {
        A  arr;
        typedef typename A::value_type type_t;
        for(std::size_t i = 0 ; i < arr.size(); ++i)
        {
#ifndef _MSC_VER
            // Initialize before use
            type_t val = {};
#else
            type_t val;
#endif
            if( type::json_traits<type_t&>::match_token_type(this->operator [](i) ) )
            {
                type::json_traits<type_t&>::extract(this->operator [](i), nullptr, val);
                arr[i] = val;
            }
            else
            {
                throw type_error( "Array item type mismatch" );
            }
        }
        return arr;
    }

};


JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_VECTOR_HPP

