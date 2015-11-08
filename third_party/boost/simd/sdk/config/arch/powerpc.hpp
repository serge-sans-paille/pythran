//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONFIG_ARCH_POWERPC_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONFIG_ARCH_POWERPC_HPP_INCLUDED

#if !defined(BOOST_SIMD_ARCH)
  #if   defined(__powerpc)    || defined(__powerpc__) \
    ||  defined(__POWERPC__)  || defined(__ppc__)     \
    ||  defined(_M_PPC)       || defined(_ARCH_PPC)   \
    ||  defined(DOXYGEN_ONLY)

    #define BOOST_SIMD_ARCH_POWERPC
    #define BOOST_SIMD_ARCH "Power PC"

  #endif
#endif
#endif
