//==================================================================================================
/**

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_UNARY_MINUS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/constant/mzero.hpp>
#include <boost/simd/constant/zero.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( unary_minus_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bs::Zero<A0>() - a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( unary_minus_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bitwise_xor(bs::Mzero<A0>(),a0);
    }
  };
  BOOST_DISPATCH_OVERLOAD_IF ( unary_minus_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::signed_<T>, X>
                           )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a0) const BOOST_NOEXCEPT
    {
      return if_else(a0 == Valmin<T>(),Valmax<T>(),bs::unary_minus(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( unary_minus_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::unspecified_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return unary_minus(a);
    }
  };

} } }

#endif
