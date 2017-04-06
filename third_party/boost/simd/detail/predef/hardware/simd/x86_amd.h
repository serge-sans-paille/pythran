/*
Copyright 2016 NumScale SAS
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_H
#define BOOST_PREDEF_HARDWARE_SIMD_X86_AMD_H

#include <boost/predef/version_number.h>
#include <boost/simd/detail/predef/hardware/simd/x86_amd/versions.h>
#include <boost/simd/detail/predef/hardware/simd/x86_amd/sse4a.h>
#include <boost/simd/detail/predef/hardware/simd/x86_amd/fma4.h>
#include <boost/simd/detail/predef/hardware/simd/x86_amd/xop.h>

/*`
 [heading `BOOST_HW_SIMD_X86_AMD`]

 The SIMD extension for x86 (AMD) (*if detected*).
 Version number depends on the most recent detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`BOOST_HW_SIMD_X86`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`BOOST_HW_SIMD_X86`] [BOOST_HW_SIMD_X86]]
     ]

 */

#define BOOST_HW_SIMD_X86_AMD BOOST_VERSION_NUMBER_NOT_AVAILABLE

#undef BOOST_HW_SIMD_X86_AMD

#if !defined(BOOST_HW_SIMD_X86_AMD)
#   define BOOST_HW_SIMD_X86_AMD BOOST_VERSION_NUMBER_NOT_AVAILABLE
#else
    // At this point, we know that we have an AMD CPU, we do need to check for
    // other x86 extensions to determine the final version number.
#   include <boost/simd/detail/predef/hardware/simd/x86.h>
#   if BOOST_HW_SIMD_X86 > BOOST_HW_SIMD_X86_AMD
#      undef BOOST_HW_SIMD_X86_AMD
#      define BOOST_HW_SIMD_X86_AMD BOOST_HW_SIMD_X86
#   endif
#   define BOOST_HW_SIMD_X86_AMD_AVAILABLE
#endif

#define BOOST_HW_SIMD_X86_AMD_NAME "x86 (AMD) SIMD"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_X86_AMD, BOOST_HW_SIMD_X86_AMD_NAME)
