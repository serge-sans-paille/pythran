//==================================================================================================
/**
  Copyright 2015 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITSET_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_BITSET_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/constant/one.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD( bitset_
                            , (typename A0, typename A1)
                            , bd::cpu_
                            , bd::scalar_< bd::arithmetic_<A0> >
                            , bd::scalar_< bd::integer_<A1> >
                            )
 {
    BOOST_FORCEINLINE A0 operator()(A0 a0, A1 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0, unsigned>;
      BOOST_ASSERT_MSG(assert_good_shift<A0>(dec(a1)), "bitset :index is out of range");

      return bitwise_or(a0, shift_left(One<i_t>(), dec(a1)));
    }
  };
} } }


#endif
