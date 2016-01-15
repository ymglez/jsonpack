/**
 *  Jsonpack - Custom string buffer implementation
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

#ifndef JSONPACK_BUFFER_HPP
#define JSONPACK_BUFFER_HPP

#include <string>
#include <cstring>

#include "exceptions.hpp"

JSONPACK_API_BEGIN_NAMESPACE

class buffer
{
public:
    buffer(size_t init_size = 8192)
        : _size(0),
          _data(nullptr),
          _alloc(init_size)

    {
        if(init_size == 0)
        {
            _data = nullptr;
        }
        else
        {
            _data = (char*) malloc(init_size);

            if(!_data)
            {
                throw alloc_error();
            }
        }
    }

    ~buffer()
    {
        if(_data != nullptr)
            free(_data);
    }

public:
    void append(const char* buf, std::size_t len)
    {
        if(_alloc - _size < len)
        {
            expand_buffer(len);
        }
        memcpy(_data + _size, buf, len);
        _size += len;
    }

    void append(const char c, std::size_t count)
    {
        if(count)
        {
            if(_alloc - _size < count)
            {
                expand_buffer(count);
            }

            std::memset(_data + _size, c, count);
            _size += count;
        }
    }

    void erase_last_comma()
    {
        if(_size > 0 && _data[_size-1] == ',')
            _size--;
    }

    char* data()
    {
        return _data;
    }

    const char* data() const
    {
        return _data;
    }

    size_t size() const
    {
        return _size;
    }

    char* release()
    {
        append("\0", 1);
        char* tmp = _data;
        _size = 0;
        _data = nullptr;
        _alloc = 0;
        return tmp;
    }

    void clear()
    {
        _size = 0;
    }

private:
    void expand_buffer(size_t len)
    {
        size_t nsize = (_alloc > 0) ?
                    _alloc * 2 : 8192;

        while(nsize < _size + len)
        {
            size_t tmp_nsize = nsize * 2;
            if (tmp_nsize <= nsize)
            {
                nsize = _size + len;
                break;
            }
            nsize = tmp_nsize;
        }

        void* tmp = realloc(_data, nsize);
        if(!tmp)
        {
            throw alloc_error();
        }

        _data = static_cast<char*>(tmp);
        _alloc = nsize;
    }

#ifndef _MSC_VER
    //Avoiding implicit default constructor
    buffer(const buffer&) = delete ;
    buffer& operator=(const buffer&) = delete ;
#else
    buffer(const buffer&) ;
    buffer& operator=(const buffer&) ;
#endif



private:
    size_t _size;
    char* _data;
    size_t _alloc;
};


JSONPACK_API_END_NAMESPACE

#endif // JSONPACK_BUFFER_HPP

