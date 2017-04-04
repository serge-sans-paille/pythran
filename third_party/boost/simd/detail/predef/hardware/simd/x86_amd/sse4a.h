/*
 * Copyright 2016 NumScale SAS
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_SSE4A_H
#define BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_SSE4A_H

#include <boost/predef/version_number.h>

/*`
 [heading `BOOST_HW_SIMD_X86_AMD_SSE4A`]

 [@https://en.wikipedia.org/wiki/SSE4##SSE4A SSE4A] x86 extension (AMD specific).

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__SSE4A__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__SSE4A__`] [BOOST_HW_SIMD_X86_AMD_SSE4A]]
     ]

 */

#define BOOST_HW_SIMD_X86_AMD_SSE4A BOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__SSE4A__)
#   undef BOOST_HW_SIMD_X86_AMD_SSE4A
#   define BOOST_HW_SIMD_X86_AMD_SSE4A BOOST_VERSION_NUMBER_AVAILABLE
#endif

#if BOOST_HW_SIMD_X86_AMD_SSE4A
#   define BOOST_HW_SIMD_X86_AMD_SSE4A_AVAILABLE
#endif

#define BOOST_HW_SIMD_X86_AMD_SSE4A_NAME "x86 (AMD) SIMD (SSE4A)"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_X86_AMD_SSE4A, BOOST_HW_SIMD_X86_AMD_SSE4A_NAME)
