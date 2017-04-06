//==================================================================================================
/*!
  @file

  Defines the SSE4A specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4A_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4A_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if BOOST_HW_SIMD_X86_AMD_SSE4A
  #include <ammintrin.h>
  #include <boost/simd/arch/x86/sse4a/as_simd.hpp>
  #include <boost/simd/arch/x86/sse4a/pack_traits.hpp>
#endif

#endif
