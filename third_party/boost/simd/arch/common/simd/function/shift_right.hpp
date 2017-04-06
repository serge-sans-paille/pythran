//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( shift_right_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>,X>
                            , bd::scalar_<bd::fundamental_<A1>>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shift_right: a shift is out of range");
      return bitwise_cast<A0> ( shift_right( bitwise_cast<bd::as_integer_t<A0, signed>>(a0)
                                          , bd::as_integer_t<A0>(a1)
                                          )
                              );
    }
  };

   BOOST_DISPATCH_OVERLOAD_IF(shift_right_
                             , (typename A0, typename A1, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::floating_<A0>, X>
                             , bs::pack_<bd::integer_<A1>, X>
                             )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
      {
        using ntype =  bd::as_integer_t<A0, signed>;
        BOOST_ASSERT_MSG(assert_good_shift<A0>(a1), "shr: a shift is out of range");
        return bitwise_cast<A0>( shift_right(bitwise_cast<ntype>(a0), a1));
      }
   };

} } }

#endif
