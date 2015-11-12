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
#ifndef BOOST_SIMD_PREPROCESSOR_ASSUME_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_ASSUME_ALIGNED_HPP_INCLUDED

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/config.hpp>

#if defined(_MSC_VER)
#define BOOST_SIMD_ASSUME_ALIGNED(Type,Ptr,Align)                              \
__assume((std::size_t)(Ptr) % Align == 0);                                     \
/**/
#elif defined(__INTEL_COMPILER)
#define BOOST_SIMD_ASSUME_ALIGNED(Type,Ptr,Align)  __assume_aligned(Ptr, Align)
#elif defined(BOOST_SIMD_GCC_VERSION) && (BOOST_SIMD_GCC_VERSION >= 40700)
#define BOOST_SIMD_ASSUME_ALIGNED(Type,Ptr,Align)                              \
Ptr = static_cast<Type>(__builtin_assume_aligned(Ptr, Align));                 \
/**/
#else
/*!
  @brief Macro wrapper for alignment assertion

  Provides a portable access to various compiler specific intrinsics to
  inform the compiler that a given pointer is aligned on a given boundary.

  @usage{preprocessor/assume_aligned.cpp}

  @param Type   Pointer type to handle
  @param Ptr    Pointer to check
  @param Align  Power of two alignment boundary to apply
**/
#define BOOST_SIMD_ASSUME_ALIGNED(Type,Ptr,Align)
#endif

#endif
