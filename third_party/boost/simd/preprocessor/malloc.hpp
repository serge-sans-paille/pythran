//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_MALLOC_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_MALLOC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
/*!
  @brief Malloc-like behavior flag

  Used on function definition, BOOST_SIMD_MALLOC flags the current function
  as having a behavior similar to @a malloc. This allows some compilers to
  optimize the code using pointer returned by such function.

  @usage{memory/simd_malloc.cpp}

**/
#define BOOST_SIMD_MALLOC
#else
#if defined(BOOST_SIMD_COMPILER_MSVC)
#define BOOST_SIMD_MALLOC   __declspec(restrict)
#define BOOST_SIMD_ALLOC_SIZE(n)
#define BOOST_SIMD_ALLOC_THROWS
#elif defined(BOOST_SIMD_GCC_LIKE)
#define BOOST_SIMD_MALLOC   __attribute__ ((malloc))
#define BOOST_SIMD_ALLOC_SIZE(n) __attribute__((alloc_size(n)))
#define BOOST_SIMD_ALLOC_THROWS __attribute__((returns_nonnull))
#else
#define BOOST_SIMD_MALLOC
#define BOOST_SIMD_ALLOC_SIZE(n)
#define BOOST_SIMD_ALLOC_THROWS
#endif
#endif

#endif
