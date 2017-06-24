//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/one.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// rec for integral types
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_OVERLOAD_IF( rec_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::uint_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return if_else_allbits(a0, if_one_else_zero(a0 == One<A0>()));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( rec_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::int_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return if_else(a0, if_else_zero(bs::abs(a0) == One<A0>(), a0), Valmax<A0>());
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// rec for floating types: take all version when no better exists reverting to division
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_OVERLOAD( rec_
                         , (typename A0, typename X)
                         , bd::cpu_
                         , bs::pack_<bd::floating_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return One<A0>()/a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( rec_
                            , (typename T, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::raw_tag
                            , bs::pack_<bd::unspecified_<T>, X>
                            )
  {
    BOOST_FORCEINLINE T operator()(const raw_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return rec(a);
    }
  };
} } }

#endif
