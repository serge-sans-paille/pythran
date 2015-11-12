//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_X86_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_X86_HPP_INCLUDED

#if !defined(BOOST_SIMD_ARCH)

  #if     defined(__x86_64__)     || defined(_M_X64)      \
      ||  defined(DOXYGEN_ONLY)
    #define BOOST_SIMD_ARCH_X86_64
  #endif

  #if     defined(BOOST_SIMD_ARCH_X86_64)                        \
      ||  defined(__i386__)       || defined(_M_IX86)     \
      ||  defined(__INTEL__)      || defined(_X86_)       \
      ||  defined(__THW_INTEL__)  || defined(DOXYGEN_ONLY)
    #define BOOST_SIMD_ARCH_X86
  #endif

  #if defined(BOOST_SIMD_ARCH_X86_64) ||  defined(DOXYGEN_ONLY)
    #define BOOST_SIMD_ARCH "Intel x86_64"
  #elif defined(BOOST_SIMD_ARCH_X86)
    #define BOOST_SIMD_ARCH "Intel x86"
  #endif

#endif
#endif
