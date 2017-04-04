//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#ifndef BOOST_SIMD_FUNCTION_SIMD_NEGATE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIMD_NEGATE_HPP_INCLUDED

#include <boost/simd/function/scalar/negate.hpp>
#include <boost/simd/arch/common/generic/function/autodispatcher.hpp>
#include <boost/simd/arch/common/simd/function/negate.hpp>

#if defined(BOOST_HW_SIMD_X86_OR_AMD_AVAILABLE)
#  if BOOST_HW_SIMD_X86_OR_AMD >= BOOST_HW_SIMD_X86_SSSE3_VERSION
#    include <boost/simd/arch/x86/ssse3/simd/function/negate.hpp>
#  endif
#endif

#endif
