/**
 *  Jsonpack - C++ compiler features
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

#ifndef JSONPACK_CONFIG_HPP
#define JSONPACK_CONFIG_HPP

#if defined __cplusplus
#   if (__cplusplus >= 201103) & !defined(_MSC_VER)
#       define JSONPACK_USE_VARIADIC_TEMPLATES
#   endif
#endif

#if defined __cplusplus
#   if (__cplusplus >= 201103) & !defined(_MSC_VER)
#       define noexcept noexcept
#   elif _MSC_VER>=1900
#   else
#		define noexcept
#   endif
#endif

/**
 * Disable unused attribute warnings
 */
#ifdef __GNUC__
#define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#define UNUSED(x) UNUSED_## x
#endif


#endif // JSONPACK_CONFIG_HPP

