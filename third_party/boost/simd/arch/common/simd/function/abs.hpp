//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ABS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ABS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/function/bitwise_notand.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/constant/maxleftshift.hpp>
#include <boost/simd/constant/mzero.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  //------------------------------------------------------------------------------------------------
  // abs on signed values
  BOOST_DISPATCH_OVERLOAD_IF( abs_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::signed_<A0>, X>
                            )
   {
      BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
      {
        A0 const s = shift_right(a0, Maxleftshift<typename A0::value_type>());
        return (a0+s)^s;
      }
   };

  //------------------------------------------------------------------------------------------------
  // abs on unsigned values is identity
  BOOST_DISPATCH_OVERLOAD( abs_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unsigned_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
      {
        return a0;
      }
   };

  //------------------------------------------------------------------------------------------------
  // abs on real values cleans the sign bit
  BOOST_DISPATCH_OVERLOAD_IF( abs_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return bitwise_notand(Mzero<A0>(),a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( abs_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::unsigned_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return a;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF ( abs_
                          , (typename T, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::saturated_tag
                          , bs::pack_<bd::floating_<T>, X>
                          )
  {
    BOOST_FORCEINLINE T operator()(const saturated_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return bs::abs(a);
    }
  };
} } }

#endif
