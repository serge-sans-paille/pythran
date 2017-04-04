/*
 * Copyright 2016 NumScale SAS
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_FMA4_H
#define BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_FMA4_H

#include <boost/predef/version_number.h>

/*`
 [heading `BOOST_HW_SIMD_X86_AMD_FMA4`]

 [@https://en.wikipedia.org/wiki/FMA_instruction_set#FMA4_instruction_set FMA4] x86 extension (AMD specific).

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__FMA4__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__FMA4__`] [BOOST_HW_SIMD_X86_AMD_FMA4]]
     ]

 */

#define BOOST_HW_SIMD_X86_AMD_FMA4 BOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__FMA4__)
#   undef BOOST_HW_SIMD_X86_AMD_FMA4
#   define BOOST_HW_SIMD_X86_AMD_FMA4 BOOST_VERSION_NUMBER_AVAILABLE
#endif

#if BOOST_HW_SIMD_X86_AMD_FMA4
#   define BOOST_HW_SIMD_X86_AMD_FMA4_AVAILABLE
#endif

#define BOOST_HW_SIMD_X86_AMD_FMA4_NAME "x86 (AMD) SIMD (FMA4)"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_X86_AMD_FMA4, BOOST_HW_SIMD_X86_AMD_FMA4_NAME)
