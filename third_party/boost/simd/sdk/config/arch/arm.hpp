//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_ARM_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_ARM_HPP_INCLUDED

#if !defined(BOOST_SIMD_ARCH)

  #if     defined(__arm__)     || defined(_ARM) ||  defined(DOXYGEN_ONLY)
    #define BOOST_SIMD_ARCH_ARM
    #define BOOST_SIMD_ARCH "ARM"
  #endif

  #if     defined(__aarch64__)
    #define BOOST_SIMD_ARCH_ARM
    #define BOOST_SIMD_ARCH_ARM_64
    #define BOOST_SIMD_ARCH "AArch64"
  #endif

#endif
#endif
