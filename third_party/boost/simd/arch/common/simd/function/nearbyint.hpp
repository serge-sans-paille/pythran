//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/raw.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( nearbyint_
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

  BOOST_DISPATCH_OVERLOAD_IF( nearbyint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      const A0 s   = bitofsign(a0);
      const A0 v   = bitwise_xor(a0, s);
      const A0 t2n = bs::Twotonmb<A0>();
      const A0 d0  = v+t2n;
      return bitwise_xor(if_else(is_less(v,t2n),d0-t2n,v), s);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( nearbyint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::raw_tag
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(raw_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return nearbyint(a0);
    }
  };
} } }

#endif

