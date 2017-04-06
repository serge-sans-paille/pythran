//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DEC_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_DEC_S_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/function/is_not_equal.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/saturated.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( dec_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &, A0 const& a0) const BOOST_NOEXCEPT
    {
      return if_dec(is_not_equal(a0, Valmin<A0>()), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( dec_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator() (const saturated_tag &, A0 const& a0) const BOOST_NOEXCEPT
    {
      return a0-One<A0>();
    }
  };
} } }


#endif
