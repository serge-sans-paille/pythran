/*
 * Copyright 2016 NumScale SAS
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 * */

#ifndef BOOST_PREDEF_HARDWARE_SIMD_X86_FMA3_H
#define BOOST_PREDEF_HARDWARE_SIMD_X86_FMA3_H

#include <boost/predef/version_number.h>

/*`
 [heading `BOOST_HW_SIMD_X86_FMA3`]

 The [@https://en.wikipedia.org/wiki/FMA_instruction_set FMA3] x86 extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__FMA__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__FMA__`] [BOOST_HW_SIMD_X86_FMA3]]
     ]

 */

#define BOOST_HW_SIMD_X86_FMA3 BOOST_VERSION_NUMBER_NOT_AVAILABLE

#if defined(__FMA__)
#   undef BOOST_HW_SIMD_X86_FMA3
#   define BOOST_HW_SIMD_X86_FMA3 BOOST_VERSION_NUMBER_AVAILABLE
#endif

#if BOOST_HW_SIMD_X86_FMA3
#   define BOOST_HW_SIMD_X86_FMA3_AVAILABLE
#endif

#define BOOST_HW_SIMD_X86_FMA3_NAME "x86 SIMD (FMA3)"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_X86_FMA3, BOOST_HW_SIMD_X86_FMA3_NAME)
