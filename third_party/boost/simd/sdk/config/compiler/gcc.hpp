//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_COMPILER_GCC_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_COMPILER_GCC_HPP_INCLUDED

#if !defined(BOOST_SIMD_COMPILER)
  #if defined(__GNUC__)

    #if !defined(__clang__) && !defined(__INTEL_COMPILER)
      #define BOOST_SIMD_COMPILER_GCC
    #endif

    #define BOOST_SIMD_COMPILER_GCC_LIKE
    #define BOOST_SIMD_COMPILER BOOST_COMPILER
    #define BOOST_SIMD_GCC_VERSION ( __GNUC__            * 10000               \
                                   + __GNUC_MINOR__      * 100                 \
                                   + __GNUC_PATCHLEVEL__                       \
                                   )


  #endif
#endif
#endif
