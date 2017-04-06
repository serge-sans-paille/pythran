//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RSQRT_HPP_INCLUDED

#include <boost/simd/function/raw.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( rsqrt_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_< bd::floating_<A0>, X >
                            )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::rec(bs::sqrt(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( rsqrt_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , boost::simd::raw_tag
                            , bs::pack_< bd::floating_<A0>, X >
                            )
  {
    BOOST_FORCEINLINE A0 operator() (const raw_tag &,  A0 const& a0) const BOOST_NOEXCEPT
    {
      return bs::rec(bs::raw_(bs::sqrt)(a0));
    }
  };
} } }

#endif
