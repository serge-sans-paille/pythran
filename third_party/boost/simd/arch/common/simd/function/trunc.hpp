//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TRUNC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TRUNC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/constant/maxflint.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/std.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  //------------------------------------------------------------------------------------------------
  // Integer cases are no-op
  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::raw_tag
                          , bs::pack_<bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(bs::raw_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( trunc_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::std_tag
                          , bs::pack_<bd::integer_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(bs::std_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };

  //------------------------------------------------------------------------------------------------
  // FP cases
  BOOST_DISPATCH_OVERLOAD_IF( trunc_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return if_else( bs::abs(a0) < Maxflint<A0>(), raw_(trunc)(a0) , a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( trunc_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::raw_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(bs::raw_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return tofloat(toint(a0));
    }
  };
} } }

#endif
