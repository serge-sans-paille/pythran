//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#ifndef BOOST_SIMD_FUNCTION_SIMD_FMA_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIMD_FMA_HPP_INCLUDED

#include <boost/simd/function/scalar/fma.hpp>
#include <boost/simd/arch/common/generic/function/autodispatcher.hpp>
#include <boost/simd/arch/common/simd/function/fma.hpp>

#if defined(BOOST_HW_SIMD_X86_OR_AMD_AVAILABLE)
#  if BOOST_HW_SIMD_X86_AMD_FMA4
#    include <boost/simd/arch/x86/fma4/simd/function/fma.hpp>
#  endif
#  if BOOST_HW_SIMD_X86_AMD_XOP
#    include <boost/simd/arch/x86/xop/simd/function/fma.hpp>
#  endif
#  if BOOST_HW_SIMD_X86_FMA3
#    include <boost/simd/arch/x86/fma3/simd/function/fma.hpp>
#  endif
#endif

#endif
