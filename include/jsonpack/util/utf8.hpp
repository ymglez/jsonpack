/**
 *  Jsonpack - utf8
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

#ifndef JSONPACK_UTF8_HPP
#define JSONPACK_UTF8_HPP

#include <string>
#include <stdint.h>

#include "jsonpack/namespace.hpp"

JSONPACK_API_BEGIN_NAMESPACE
UTIL_BEGIN_NAMESPACE

struct utf8
{
    typedef uint32_t uchar_t;

    static std::size_t validate_char(const char *str)
    {
        unsigned char c = (unsigned char)*str++;

        if (c <= 0x7F)
        {        /* 00..7F */
            return 1;
        }
        else if (c <= 0xC1) { /* 80..C1 */
            /* Disallow overlong 2-byte sequence. */
            return 0;
        }
        else if (c <= 0xDF)
        {
            /* Make sure subsequent byte is in the range 0x80..0xBF. */
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;

            return 2;
        }
        else if (c <= 0xEF)
        { /* E0..EF */
            /* Disallow overlong 3-byte sequence. */
            if (c == 0xE0 && (unsigned char)*str < 0xA0)
                return 0;

            /* Disallow U+D800..U+DFFF. */
            if (c == 0xED && (unsigned char)*str > 0x9F)
                return 0;

            /* Make sure subsequent bytes are in the range 0x80..0xBF. */
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;

            return 3;
        }
        else if (c <= 0xF4)
        { /* F0..F4 */
            /* Disallow overlong 4-byte sequence. */
            if (c == 0xF0 && (unsigned char)*str < 0x90)
                return 0;

            /* Disallow codepoints beyond U+10FFFF. */
            if (c == 0xF4 && (unsigned char)*str > 0x8F)
                return 0;

            /* Make sure subsequent bytes are in the range 0x80..0xBF. */
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;
            if (((unsigned char)*str++ & 0xC0) != 0x80)
                return 0;

            return 4;
        }
        else
        {                /* F5..FF */
            return 0;
        }
    }

    /* Validate a null-terminated UTF-8 string. */
    static bool validate(const char *str)
    {
        std::size_t len = 0;

        for (; *str != 0; str += len)
        {
            len = validate_char(str);
            if (len == 0)
                return false;
        }

        return true;
    }

    static int read_char(const char *s, uchar_t &out)
    {
        const unsigned char *c = (const unsigned char*) s;

        assert(validate_char(s));

        if (c[0] <= 0x7F)
        {
            /* 00..7F */
            out = c[0];
            return 1;
        }
        else if (c[0] <= 0xDF)
        {
            /* C2..DF (unless input is invalid) */
            out = ((uchar_t)c[0] & 0x1F) << 6 |
                                             ((uchar_t)c[1] & 0x3F);
            return 2;
        }
        else if (c[0] <= 0xEF)
        {
            /* E0..EF */
            out = ((uchar_t)c[0] &  0xF) << 12 |
                                             ((uchar_t)c[1] & 0x3F) << 6  |
                                                                       ((uchar_t)c[2] & 0x3F);
            return 3;
        }
        else
        {
            /* F0..F4 (unless input is invalid) */
            out = ((uchar_t)c[0] &  0x7) << 18 |
                                             ((uchar_t)c[1] & 0x3F) << 12 |
                                                                       ((uchar_t)c[2] & 0x3F) << 6  |
                                                                                                 ((uchar_t)c[3] & 0x3F);
            return 4;
        }
    }

    /*
     * Write a single UTF-8 character to @s,
     * returning the length, in bytes, of the character written.
     *
     * @unicode must be U+0000..U+10FFFF, but not U+D800..U+DFFF.
     *
     * This function will write up to 4 bytes to @out.
     */
    static int write_char(const uchar_t &codepoint, char *out)
    {
        unsigned char *o = (unsigned char*) out;

        assert(codepoint <= 0x10FFFF && !(codepoint >= 0xD800 && codepoint <= 0xDFFF));

        if (codepoint <= 0x7F)
        {
            /* U+0000..U+007F */
            *(o++) = (unsigned char)codepoint;
            return 1;
        }
        else if (codepoint <= 0x7FF)
        {
            /* U+0080..U+07FF */
            *(o++) = static_cast<unsigned char>((0xC0 | ((codepoint >> 6) & 0xFF)));
            *(o++) = static_cast<unsigned char>(0x80 | ((codepoint & 0x3F)));
            return 2;
        }
        else if (codepoint <= 0xFFFF)
        {
            /* U+0800..U+FFFF */
            *(o++) = static_cast<unsigned char>(0xE0 | ((codepoint >> 12) & 0xFF));
            *(o++) = static_cast<unsigned char>(0x80 | ((codepoint >> 6) & 0x3F));
            *(o++) = static_cast<unsigned char>(0x80 | (codepoint & 0x3F));
            return 3;
        }
        else
        {
            /* U+10000..U+10FFFF */
            *(o++) = static_cast<unsigned char>(0xF0 | ((codepoint >> 18) & 0xFF));
            *(o++) = static_cast<unsigned char>(0x80 | ((codepoint >> 12) & 0x3F));
            *(o++) = static_cast<unsigned char>(0x80 | ((codepoint >> 6) & 0x3F));
            *(o++) = static_cast<unsigned char>(0x80 | (codepoint & 0x3F));
            return 4;
        }
    }

    /*
     * Compute the Unicode codepoint of a UTF-16 surrogate pair.
     *
     * @uc should be 0xD800..0xDBFF, and @lc should be 0xDC00..0xDFFF.
     * If they aren't, this function returns false.
     */
    static bool from_surrogate_pair(const uint16_t uc, const uint16_t &lc, uchar_t &codepoint)
    {
        if (uc >= 0xD800 && uc <= 0xDBFF && lc >= 0xDC00 && lc <= 0xDFFF)
        {
            codepoint = 0x10000 + ((((uchar_t)uc & 0x3FF) << 10) | (lc & 0x3FF));
            return true;
        }
        else
        {
            return false;
        }
    }

    /*
     * Construct a UTF-16 surrogate pair given a Unicode codepoint.
     *
     */
    static void to_surrogate_pair(const uchar_t &codepoint, uint16_t &uc, uint16_t &lc)
    {
        uchar_t n;

        assert(codepoint >= 0x10000 && codepoint <= 0x10FFFF);

        n = codepoint - 0x10000;
        uc = (uint16_t)(((n >> 10) & 0x3FF) | 0xD800);
        lc = (uint16_t)((n & 0x3FF) | 0xDC00);
    }
};


JSONPACK_API_END_NAMESPACE //util
JSONPACK_API_END_NAMESPACE // jsonpack

#endif // JSONPACK_UTF8_HPP

