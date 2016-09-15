//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_SHIFT_RIGHT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( shift_right_
                          , (typename A0, typename A1)
                          , bs::vmx_
                          , bs::pack_<bd::int_<A0>, bs::vmx_>
                          , bs::pack_<bd::integer_<A1>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( assert_good_shift<A0>(a1)
                      , "shift_right: a shift is out of range"
                      );

     return vec_sra(a0.storage(), bitwise_cast<bd::as_unsigned_t<A1>>(a1).storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shift_right_
                          , (typename A0, typename A1)
                          , bs::vmx_
                          , bs::pack_<bd::uint_<A0>, bs::vmx_>
                          , bs::pack_<bd::integer_<A1>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( assert_good_shift<A0>(a1)
                      , "shift_right: a shift is out of range"
                      );

     return vec_sr(a0.storage(), bitwise_cast<bd::as_unsigned_t<A1>>(a1).storage());
    }
  };
} } }

#endif
