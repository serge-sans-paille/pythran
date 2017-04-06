//==================================================================================================
/*
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MAX_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MAX_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/pedantic.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_nan.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( max_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return if_else(is_less(a0, a1), a1, a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( max_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pedantic_tag
                            , bs::pack_<bd::integer_<A0>, X>
                            , bs::pack_<bd::integer_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( pedantic_tag const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return bs::max(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( max_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pedantic_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( pedantic_tag const&
                                   , const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return if_else(is_nan(a1), a0, bs::max(a0, a1));
    }
  };
} } }

#endif
