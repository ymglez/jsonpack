/*
 Formatting library for C++

 Copyright (c) 2012 - 2015, Victor Zverovich
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this
    list of conditions and the following disclaimer.
 2. Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "jsonpack/3rdparty/format.h"

#include <string.h>

#include <cctype>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdarg>


#if defined(_WIN32) && defined(__MINGW32__)
# include <cstring>
#endif

namespace fmt {

#ifndef _MSC_VER
# define FMT_SNPRINTF snprintf
#else  // _MSC_VER
inline int fmt_snprintf(char *buffer, size_t size, const char *format, ...) {
    va_list args;
    va_start(args, format);
    int result = vsnprintf_s(buffer, size, _TRUNCATE, format, args);
    va_end(args);
    return result;
}
# define FMT_SNPRINTF fmt_snprintf
#endif  // _MSC_VER

const char fmt::internal::BasicData::DIGITS[] =
        "0001020304050607080910111213141516171819"
        "2021222324252627282930313233343536373839"
        "4041424344454647484950515253545556575859"
        "6061626364656667686970717273747576777879"
        "8081828384858687888990919293949596979899";

#define FMT_POWERS_OF_10(factor) \
    factor * 10, \
    factor * 100, \
    factor * 1000, \
    factor * 10000, \
    factor * 100000, \
    factor * 1000000, \
    factor * 10000000, \
    factor * 100000000, \
    factor * 1000000000

const uint32_t internal::BasicData::POWERS_OF_10_32[] = {
    0, FMT_POWERS_OF_10(1)
};

const uint64_t internal::BasicData::POWERS_OF_10_64[] = {
    0,
    FMT_POWERS_OF_10(1),
    FMT_POWERS_OF_10(fmt::ULongLong(1000000000)),
    // Multiply several constants instead of using a single long long constant
    // to avoid warnings about C++98 not supporting long long.
    fmt::ULongLong(1000000000) * fmt::ULongLong(1000000000) * 10
};
}
