//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SPEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SPEC_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>

#if !defined(BOOST_SIMD_DEFAULT_FAMILY)
  #if BOOST_HW_SIMD_PPC == BOOST_HW_SIMD_PPC_VMX_VERSION
    #define BOOST_SIMD_DEFAULT_FAMILY   ::boost::simd::vmx_
    #define BOOST_SIMD_DEFAULT_SITE     ::boost::simd::vmx_
  #endif
#endif


#if BOOST_HW_SIMD_PPC >= BOOST_HW_SIMD_PPC_VMX_VERSION
  // No Denormals on VMX familly
# ifndef BOOST_SIMD_NO_DENORMALS
#   define BOOST_SIMD_NO_DENORMALS
# endif

/*
  Include the proper intrinsic include. Depending of the option used by the
  compiler (-faltivec or -maltivec), we need to include altivec.h or not.
*/
# if !defined(__APPLE_CC__) || __APPLE_CC__ <= 1 || __GNUC__ >= 4
#   include <altivec.h>
# endif

// Cleanup C++ kludge macro
# ifdef bool
#   undef bool
# endif
# ifdef pixel
#   undef pixel
# endif
# ifdef vector
#   undef vector
# endif

# if defined(__IBMCPP__) || defined(__MWERKS__)
#   define __bool bool
# endif

#include <boost/simd/arch/ppc/vmx/as_simd.hpp>
#include <boost/simd/arch/ppc/vmx/pack_traits.hpp>
#endif

#endif
