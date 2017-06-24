//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_COMMON_REGISTER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_COMMON_REGISTER_HPP_INCLUDED
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/predef.hpp>

#if BOOST_HW_SIMD_X86
namespace boost { namespace simd
{
  struct register_count
  {
    using general = nsm::size_t<2*sizeof(void*)>;
    using simd    = nsm::size_t<2*sizeof(void*)>;
  };
} }
#endif

#endif
