//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================

#ifndef BOOST_SIMD_FUNCTION_SIMD_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIMD_COMPLEMENT_HPP_INCLUDED

#include <boost/simd/function/scalar/complement.hpp>
#include <boost/simd/arch/common/generic/function/autodispatcher.hpp>
#include <boost/simd/arch/common/simd/function/complement.hpp>

#if defined(BOOST_HW_SIMD_PPC_AVAILABLE)
#  if BOOST_HW_SIMD_PPC >= BOOST_HW_SIMD_PPC_VMX_VERSION
#    include <boost/simd/arch/ppc/vmx/simd/function/complement.hpp>
#  endif
#endif

#endif
