//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_OS_NIX_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_OS_NIX_HPP_INCLUDED

#if !defined(BOOST_SIMD_OS)
  #if     defined(linux)      ||  defined(__linux)                          \
      ||  defined(__linux__)  ||  defined(__unix)  || defined(DOXYGEN_ONLY) \

    #define BOOST_SIMD_OS_LINUX
    #define BOOST_SIMD_OS BOOST_PLATFORM

  #endif
#endif

#endif
