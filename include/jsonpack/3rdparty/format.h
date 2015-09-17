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

#ifndef FMT_FORMAT_H_
#define FMT_FORMAT_H_

#include <stdint.h>

#include <cassert>
#include <cmath>
#include <cstddef>  // for std::ptrdiff_t
#include <cstdio>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <string>
#include <sstream>
#include <map>



#if _SECURE_SCL
# include <iterator>
#endif

#ifdef _MSC_VER
# include <intrin.h>  // _BitScanReverse, _BitScanReverse64

namespace fmt {
namespace internal {
# pragma intrinsic(_BitScanReverse)
inline uint32_t clz(uint32_t x) {
    unsigned long r = 0;
    _BitScanReverse(&r, x);
    return 31 - r;
}
# define FMT_BUILTIN_CLZ(n) fmt::internal::clz(n)

# ifdef _WIN64
#  pragma intrinsic(_BitScanReverse64)
# endif

inline uint32_t clzll(uint64_t x) {
    unsigned long r = 0;
# ifdef _WIN64
    _BitScanReverse64(&r, x);
# else
    // Scan the high 32 bits.
    if (_BitScanReverse(&r, static_cast<uint32_t>(x >> 32)))
        return 63 - (r + 32);

    // Scan the low 32 bits.
    _BitScanReverse(&r, static_cast<uint32_t>(x));
# endif
    return 63 - r;
}
# define FMT_BUILTIN_CLZLL(n) fmt::internal::clzll(n)
}
}
#endif

#ifdef __GNUC__
# define FMT_GCC_VERSION (__GNUC__ * 100 + __GNUC_MINOR__)
# define FMT_GCC_EXTENSION __extension__
# if FMT_GCC_VERSION >= 406
#  pragma GCC diagnostic push
// Disable the warning about "long long" which is sometimes reported even
// when using __extension__.
#  pragma GCC diagnostic ignored "-Wlong-long"
// Disable the warning about declaration shadowing because it affects too
// many valid cases.
#  pragma GCC diagnostic ignored "-Wshadow"
# endif
# if __cplusplus >= 201103L || defined __GXX_EXPERIMENTAL_CXX0X__
#  define FMT_HAS_GXX_CXX11 1
# endif
#else
# define FMT_GCC_EXTENSION
#endif

#ifdef __clang__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdocumentation"
#endif

#ifdef __GNUC_LIBSTD__
# define FMT_GNUC_LIBSTD_VERSION (__GNUC_LIBSTD__ * 100 + __GNUC_LIBSTD_MINOR__)
#endif

#ifdef __has_feature
# define FMT_HAS_FEATURE(x) __has_feature(x)
#else
# define FMT_HAS_FEATURE(x) 0
#endif

#ifdef __has_builtin
# define FMT_HAS_BUILTIN(x) __has_builtin(x)
#else
# define FMT_HAS_BUILTIN(x) 0
#endif

#ifdef __has_cpp_attribute
# define FMT_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
# define FMT_HAS_CPP_ATTRIBUTE(x) 0
#endif

#ifndef FMT_USE_VARIADIC_TEMPLATES
// Variadic templates are available in GCC since version 4.4
// (http://gcc.gnu.org/projects/cxx0x.html) and in Visual C++
// since version 2013.
# define FMT_USE_VARIADIC_TEMPLATES \
    (FMT_HAS_FEATURE(cxx_variadic_templates) || \
    (FMT_GCC_VERSION >= 404 && FMT_HAS_GXX_CXX11) || _MSC_VER >= 1800)
#endif

#ifndef FMT_USE_RVALUE_REFERENCES
// Don't use rvalue references when compiling with clang and an old libstdc++
// as the latter doesn't provide std::move.
# if defined(FMT_GNUC_LIBSTD_VERSION) && FMT_GNUC_LIBSTD_VERSION <= 402
#  define FMT_USE_RVALUE_REFERENCES 0
# else
#  define FMT_USE_RVALUE_REFERENCES \
    (FMT_HAS_FEATURE(cxx_rvalue_references) || \
    (FMT_GCC_VERSION >= 403 && FMT_HAS_GXX_CXX11) || _MSC_VER >= 1600)
# endif
#endif

#if FMT_USE_RVALUE_REFERENCES
# include <utility>  // for std::move
#endif

// Define FMT_USE_NOEXCEPT to make C++ Format use noexcept (C++11 feature).
#ifndef FMT_NOEXCEPT
# if FMT_USE_NOEXCEPT || FMT_HAS_FEATURE(cxx_noexcept) || \
    (FMT_GCC_VERSION >= 408 && FMT_HAS_GXX_CXX11)
#  define FMT_NOEXCEPT noexcept
# else
#  define FMT_NOEXCEPT throw()
# endif
#endif

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#if FMT_USE_DELETED_FUNCTIONS || FMT_HAS_FEATURE(cxx_deleted_functions) || \
    (FMT_GCC_VERSION >= 404 && FMT_HAS_GXX_CXX11) || _MSC_VER >= 1800
# define FMT_DELETED_OR_UNDEFINED  = delete
# define FMT_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&) = delete; \
    TypeName& operator=(const TypeName&) = delete
#else
# define FMT_DELETED_OR_UNDEFINED
# define FMT_DISALLOW_COPY_AND_ASSIGN(TypeName) \
    TypeName(const TypeName&); \
    TypeName& operator=(const TypeName&)
#endif

#ifndef FMT_ASSERT
# define FMT_ASSERT(condition, message) assert((condition) && message)
#endif

namespace fmt {

// Fix the warning about long long on older versions of GCC
// that don't support the diagnostic pragma.
FMT_GCC_EXTENSION typedef long long LongLong;
FMT_GCC_EXTENSION typedef unsigned long long ULongLong;


namespace internal {


// Static data is placed in this class template to allow header-only
// configuration.
struct BasicData {
    static const uint32_t POWERS_OF_10_32[] ;

    static const uint64_t POWERS_OF_10_64[] ;

    static const char DIGITS[];
};

typedef BasicData Data;
}


/**
  Fast integer formatter.
 */
class FormatInt {
private:
    // Buffer should be large enough to hold all digits (digits10 + 1),
    // a sign and a null character.
    enum {BUFFER_SIZE = std::numeric_limits<ULongLong>::digits10 + 3};
    mutable char buffer_[BUFFER_SIZE];
    char *str_;

    // Formats value in reverse and returns the number of digits.
    char *format_decimal(ULongLong value) {
        char *buffer_end = buffer_ + BUFFER_SIZE - 1;
        while (value >= 100) {
            // Integer division is slow so do it for a group of two digits instead
            // of for every digit. The idea comes from the talk by Alexandrescu
            // "Three Optimization Tips for C++". See speed-test for a comparison.
            unsigned index = (value % 100) * 2;
            value /= 100;
            *--buffer_end = internal::Data::DIGITS[index + 1];
            *--buffer_end = internal::Data::DIGITS[index];
        }
        if (value < 10) {
            *--buffer_end = static_cast<char>('0' + value);
            return buffer_end;
        }
        unsigned index = static_cast<unsigned>(value * 2);
        *--buffer_end = internal::Data::DIGITS[index + 1];
        *--buffer_end = internal::Data::DIGITS[index];
        return buffer_end;
    }

    void FormatSigned(LongLong value) {
        ULongLong abs_value = static_cast<ULongLong>(value);
        bool negative = value < 0;
        if (negative)
            abs_value = 0 - abs_value;
        str_ = format_decimal(abs_value);
        if (negative)
            *--str_ = '-';
    }

public:
    explicit FormatInt(int value):str_() { FormatSigned(value); }
    explicit FormatInt(long value):str_() { FormatSigned(value); }
    explicit FormatInt(LongLong value):str_() { FormatSigned(value); }
    explicit FormatInt(unsigned value) : str_(format_decimal(value)) {}
    explicit FormatInt(unsigned long value) : str_(format_decimal(value)) {}
    explicit FormatInt(ULongLong value) : str_(format_decimal(value)) {}

    /**
    Returns the number of characters written to the output buffer.
   */
    std::size_t size() const { return buffer_ - str_ + BUFFER_SIZE - 1; }

    /**
    Returns a pointer to the output buffer content. No terminating null
    character is appended.
   */
    const char *data() const { return str_; }

    /**
    Returns a pointer to the output buffer content with terminating null
    character appended.
   */
    const char *c_str() const {
        buffer_[BUFFER_SIZE - 1] = '\0';
        return str_;
    }

    /**
    \rst
    Returns the content of the output buffer as an ``std::string``.
    \endrst
   */
    std::string str() const { return std::string(str_, size()); }
};

}


#endif  // FMT_FORMAT_H_
