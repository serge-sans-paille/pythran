/*
 * Copyright 2016 NumScale 2016
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_XOP_H
#define BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_XOP_H

#include <boost/predef/version_number.h>

/*`
 [heading `BOOST_HW_SIMD_X86_AMD_XOP`]

 [@https://en.wikipedia.org/wiki/XOP_instruction_set XOP] x86 extension (AMD specific).

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__XOP__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__XOP__`] [BOOST_HW_SIMD_X86_AMD_XOP]]
     ]

 */

#define BOOST_HW_SIMD_X86_AMD_XOP BOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__XOP__)
#   undef BOOST_HW_SIMD_X86_AMD_XOP
#   define BOOST_HW_SIMD_X86_AMD_XOP BOOST_VERSION_NUMBER_AVAILABLE
#endif

#if BOOST_HW_SIMD_X86_AMD_XOP
#   define BOOST_HW_SIMD_X86_AMD_XOP_AVAILABLE
#endif

#define BOOST_HW_SIMD_X86_AMD_XOP_NAME "x86 (AMD) SIMD (XOP)"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_X86_AMD_XOP, BOOST_HW_SIMD_X86_AMD_XOP_NAME)
