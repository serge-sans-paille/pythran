//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_IA64_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_IA64_HPP_INCLUDED

#if !defined(BOOST_SIMD_ARCH)
  #if defined(__ia64__)  || defined(_IA64)   || defined(__IA64__)   ||\
      defined(__ia64)    || defined(_M_IA64) || defined(DOXYGEN_ONLY) \

    #define BOOST_SIMD_ARCH_IA64
    #define BOOST_SIMD_ARCH "Intel 64"

  #endif
#endif
#endif
