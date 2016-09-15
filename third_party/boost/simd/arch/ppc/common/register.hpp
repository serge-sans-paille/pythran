//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_COMMON_REGISTER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_COMMON_REGISTER_HPP_INCLUDED

#include <boost/predef/architecture.h>

#if BOOST_HW_SIMD_PPC
namespace boost { namespace simd
{
  struct register_count
  {
    using general = 32;
#if BOOST_HW_SIMD_PPC == BOOST_HW_SIMD_PPC_VMX_VERSION
    using simd    = 32;
#else
    using simd    = 64;
#endif

  };
} }
#endif

#endif
