/**
 *  Jsonpack - Error management
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

#ifndef JSONPACK_EXCEPTIONS_HPP
#define JSONPACK_EXCEPTIONS_HPP

#include <stdexcept>

#include "jsonpack/namespace.hpp"

JSONPACK_API_BEGIN_NAMESPACE

/**
 *
 */
class jsonpack_error : public std::runtime_error
{
public:
    jsonpack_error() : std::runtime_error(""){}
    jsonpack_error(const char* what): std::runtime_error(what){}
};

/**
 *
 */
class invalid_json : public jsonpack_error
{
public:
    invalid_json(){}
    invalid_json(const char* what): jsonpack_error(what){}
};


/**
 *
 */
class type_error : public jsonpack_error
{
public:
    type_error(){}
    type_error(const char* what): jsonpack_error(what){}
};

/**
 *
 */
class alloc_error : public jsonpack_error
{
public:
    alloc_error(){}
    alloc_error(const char* what): jsonpack_error(what){}
};


JSONPACK_API_END_NAMESPACE

#endif

