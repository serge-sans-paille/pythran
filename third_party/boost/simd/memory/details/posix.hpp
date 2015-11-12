//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_DETAILS_POSIX_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_DETAILS_POSIX_HPP_INCLUDED

#if defined(unix) || defined(__unix__) || defined(__unix)
#include <unistd.h>
#endif

// Check if posix_memalign is supported
#if (     (defined _GNU_SOURCE)                                   \
      ||  ((defined _XOPEN_SOURCE) && (_XOPEN_SOURCE >= 600))     \
    )                                                             \
 && (defined _POSIX_ADVISORY_INFO) && (_POSIX_ADVISORY_INFO > 0)
  #define BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif

// Mac OS X 10.6+ special case
#if !defined(BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN) && defined(__APPLE__)
#include <AvailabilityMacros.h>
#if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_6
#define BOOST_SIMD_CONFIG_SUPPORT_POSIX_MEMALIGN
#endif
#endif

#endif
