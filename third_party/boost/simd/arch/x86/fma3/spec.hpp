//==================================================================================================
/*!
  @file

  Defines the FMA3 specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_FMA3_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_FMA3_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if BOOST_HW_SIMD_X86_FMA3
  #include <immintrin.h>
  #include <boost/simd/arch/x86/fma3/as_simd.hpp>
  #include <boost/simd/arch/x86/fma3/pack_traits.hpp>
#endif

#endif
