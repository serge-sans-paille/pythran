//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_NOT_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( is_not_equal_
                            , (typename A0,typename X)
                            , detail::is_native<X>
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            )
   {
    BOOST_FORCEINLINE
    bs::as_logical_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return !(a0 == a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( is_not_equal_
                            , (typename A0,typename X)
                            , ( nsm::and_ < bs::is_bitwise_logical_t<A0>
                                              , detail::is_native<X>
                                              >
                              )
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>,X>
                            , bs::pack_<bs::logical_<A0>,X>
                            )
   {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      using cast_t = bs::as_arithmetic_t<A0>;
      return bitwise_cast<A0>(bitwise_xor(bitwise_cast<cast_t>(a0),bitwise_cast<cast_t>(a1)));
    }
  };
} } }

#endif
