/*
Copyright 2016 NumScale SAS
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_PREDEF_HARDWARE_SIMD_MIC_H
#define BOOST_PREDEF_HARDWARE_SIMD_MIC_H

#include <boost/predef/version_number.h>
#include <boost/simd/detail/predef/hardware/simd/mic/versions.h>

/*`
 [heading `BOOST_HW_SIMD_MIC`]

 The SIMD extension for MIC (*if detected*).
 Version number depends on the most recent detected extension.

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__MIC__`] [__predef_detection__]]
     ]

 [table
     [[__predef_symbol__] [__predef_version__]]

     [[`__MIC__`] [BOOST_HW_SIMD_MIC_IMCI_VERSION]]
     ]

 */

#define BOOST_HW_SIMD_MIC BOOST_VERSION_NUMBER_NOT_AVAILABLE

#undef BOOST_HW_SIMD_MIC
#if !defined(BOOST_HW_SIMD_MIC) && defined(__MIC__)
#   define BOOST_HW_SIMD_MIC BOOST_HW_SIMD_MIC_IMCI_VERSION
#endif

#if !defined(BOOST_HW_SIMD_MIC)
#   define BOOST_HW_SIMD_MIC BOOST_VERSION_NUMBER_NOT_AVAILABLE
#else
#   define BOOST_HW_SIMD_MIC_AVAILABLE
#endif

#define BOOST_HW_SIMD_MIC_NAME "IMCI SIMD"

#endif

#include <boost/predef/detail/test.h>
BOOST_PREDEF_DECLARE_TEST(BOOST_HW_SIMD_MIC, BOOST_HW_SIMD_MIC_NAME)
