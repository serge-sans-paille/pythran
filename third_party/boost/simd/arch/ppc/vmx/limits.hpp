//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_LIMITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_LIMITS_HPP_INCLUDED

#include <boost/simd/arch/ppc/tags.hpp>
#include <boost/simd/arch/common/limits.hpp>
#include <boost/simd/detail/dispatch/meta/make_integer.hpp>
#include <boost/simd/detail/brigand.hpp>
#include <cstdint>

namespace boost { namespace simd
{
  template<> struct limits<boost::simd::vmx_>
  {
    using parent = boost::simd::simd_;

    struct largest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<4,Sign> {};
    };

    struct smallest_integer
    {
      template<typename Sign> struct apply : boost::dispatch::make_integer<1,Sign> {};
    };

    using largest_real   = float;
    using smallest_real  = float;

    enum { bits = 128, bytes = 16 };
  };
} }

#endif
