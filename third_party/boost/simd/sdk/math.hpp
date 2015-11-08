//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MATH_HPP_INCLUDED
#define BOOST_SIMD_SDK_MATH_HPP_INCLUDED

#if defined(unix) || defined(__unix__) || defined(__unix)
#include <unistd.h>
#endif

// C99 / POSIX.1-2001
#if (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L) || (defined(_POSIX_VERSION) && _POSIX_VERSION >= 200112L)
#define BOOST_SIMD_HAS_TGAMMA
#define BOOST_SIMD_HAS_TGAMMAF
#define BOOST_SIMD_HAS_LGAMMA
#define BOOST_SIMD_HAS_LGAMMAF
#define BOOST_SIMD_HAS_CBRT
#define BOOST_SIMD_HAS_CBRTF
#define BOOST_SIMD_HAS_REMQUO
#define BOOST_SIMD_HAS_REMQUOF
#define BOOST_SIMD_HAS_LOGB
#define BOOST_SIMD_HAS_LOGBF
#define BOOST_SIMD_HAS_ILOGB
#define BOOST_SIMD_HAS_ILOGBF
#define BOOST_SIMD_HAS_COPYSIGN
#define BOOST_SIMD_HAS_COPYSIGNF
#define BOOST_SIMD_HAS_NEXTAFTER
#define BOOST_SIMD_HAS_NEXTAFTERF
#define BOOST_SIMD_HAS_HYPOT
#define BOOST_SIMD_HAS_HYPOTF
#define BOOST_SIMD_HAS_ISNAN
#define BOOST_SIMD_HAS_ISNANF
#define BOOST_SIMD_HAS_FPCLASSIFY
#define BOOST_SIMD_HAS_ROUNDF
#define BOOST_SIMD_HAS_ROUND
#define BOOST_SIMD_HAS_CEILF
#define BOOST_SIMD_HAS_FLOORF
#define BOOST_SIMD_HAS_TRUNCF
#define BOOST_SIMD_HAS_FABSF
#define BOOST_SIMD_HAS_SQRTF
#define BOOST_SIMD_HAS_FREXP
#define BOOST_SIMD_HAS_FREXPF
#endif

// POSIX.1-2001
#if defined(_POSIX_VERSION) && _POSIX_VERSION >= 200112L
#define BOOST_SIMD_HAS_Y0
#define BOOST_SIMD_HAS_Y1
#define BOOST_SIMD_HAS_YN
#define BOOST_SIMD_HAS_J0
#define BOOST_SIMD_HAS_J1
#define BOOST_SIMD_HAS_JN
#endif

// SUSv3
#if defined(_SVID_SOURCE) || defined(_BSD_SOURCE) || (defined(_XOPEN_SOURCE) && _XOPEN_SOURCE >= 600)
#define BOOST_SIMD_HAS_Y0F
#define BOOST_SIMD_HAS_Y1F
#define BOOST_SIMD_HAS_YNF
#define BOOST_SIMD_HAS_J0F
#define BOOST_SIMD_HAS_J1F
#define BOOST_SIMD_HAS_JNF
#endif

// Microsoft
#if defined(_MSC_VER) || defined(__MSVCRT__)
#define BOOST_SIMD_HAS__Y0
#define BOOST_SIMD_HAS__Y1
#define BOOST_SIMD_HAS__YN
#define BOOST_SIMD_HAS__J0
#define BOOST_SIMD_HAS__J1
#define BOOST_SIMD_HAS__JN
#define BOOST_SIMD_HAS__COPYSIGN
#define BOOST_SIMD_HAS__NEXTAFTER
#define BOOST_SIMD_HAS__LOGB
#define BOOST_SIMD_HAS__ISNAN
#define BOOST_SIMD_HAS__HYPOT
#define BOOST_SIMD_HAS__HYPOTF
#define BOOST_SIMD_HAS__FPCLASS
#define BOOST_SIMD_HAS_CEILF
#define BOOST_SIMD_HAS_FLOORF
#define BOOST_SIMD_HAS_FABSF
#define BOOST_SIMD_HAS_SQRTF
#define BOOST_SIMD_HAS_FREXP
#define BOOST_SIMD_HAS_FREXPF
#endif

// Microsoft x64
#if defined(_MSC_VER) && defined(_M_X64)
#define BOOST_SIMD_HAS__COPYSIGNF
#define BOOST_SIMD_HAS__NEXTAFTERF
#define BOOST_SIMD_HAS__LOGBF
#define BOOST_SIMD_HAS__ISNANF
#define BOOST_SIMD_HAS__FPCLASSF
#endif

#include <math.h>

#endif
