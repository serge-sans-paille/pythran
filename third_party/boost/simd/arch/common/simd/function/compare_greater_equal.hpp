//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPARE_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPARE_GREATER_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/compare_less.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( compare_greater_equal_
                          , (typename X, typename A0)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>, X>
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bool operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return !compare_less(a0, a1);
    }
  };
} } }

#endif

