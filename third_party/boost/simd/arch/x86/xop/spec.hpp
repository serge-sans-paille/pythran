//==================================================================================================
/*!
  @file

  Defines the XOP specifications

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if BOOST_HW_SIMD_X86_AMD_XOP
  // XOP header not standardized
  #ifdef _MSC_VER
    #include <intrin.h>
  #else
    #include <x86intrin.h>
    #include <xopintrin.h>
  #endif
  #include <boost/simd/arch/x86/xop/as_simd.hpp>
  #include <boost/simd/arch/x86/xop/pack_traits.hpp>
#endif

#endif
