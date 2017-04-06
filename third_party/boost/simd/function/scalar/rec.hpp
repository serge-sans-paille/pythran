//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#ifndef BOOST_SIMD_FUNCTION_SCALAR_REC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SCALAR_REC_HPP_INCLUDED

#include <boost/simd/function/definition/rec.hpp>
#include <boost/simd/arch/common/scalar/function/rec.hpp>

#if defined(BOOST_HW_SIMD_X86_OR_AMD_AVAILABLE)
#  if BOOST_HW_SIMD_X86_OR_AMD >= BOOST_HW_SIMD_X86_SSE_VERSION
#    include <boost/simd/arch/x86/sse1/scalar/function/rec.hpp>
#  endif
#endif

#endif
