//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_ALIGN_ON_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(DOXYGEN_ONLY)
/*!
  @brief Macro wrapper for alignment attribute

  Provides a portable access to various compiler specific attributes
  flagging types as aligned on a given boundary.

  @usage{preprocessor/align_on.cpp}

  @param Align Power of two alignment boundary to apply
**/
#define BOOST_SIMD_ALIGN_ON(Align)
#else

#if defined(__CUDACC__)
  #define BOOST_SIMD_ALIGN_ON(Align) __align__(Align)
#elif defined(_MSC_VER)
  #define BOOST_SIMD_ALIGN_ON(Align)  __declspec(align(Align))
#elif (defined(__GNUC__)) || (defined(__xlC__))
  #define BOOST_SIMD_ALIGN_ON(Align)  __attribute__(( __aligned__((Align)) ))
#elif !(defined(__WAVE__))
  #error BOOST_SIMD_ALIGN_ON - No Supported alignment attribute
#endif

#endif

#endif
