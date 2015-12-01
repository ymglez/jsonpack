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

#include "jsonpack/parser.hpp"
#include "jsonpack/exceptions.hpp"
#include "jsonpack/config.hpp"

JSONPACK_API_BEGIN_NAMESPACE

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

private:
    base_vector _vect;
	jsonpack::parser _p;

public:
    vector():_vect()
    {}

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
            throw jsonpack_error( _p.err_msg().c_str() );
    }

};


JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_VECTOR_HPP

