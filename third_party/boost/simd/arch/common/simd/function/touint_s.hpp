//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOUINT_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOUINT_S_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_ngez.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/function/touint.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( touint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::int_<A0>, X>
                            )
  {
    using result = bd::as_integer_t<A0, unsigned>;
    BOOST_FORCEINLINE result operator()(const saturated_tag &, A0 const& a0) const
    {
      return bitwise_cast<result>(saturate<result>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD( touint_
                         , (typename A0, typename X)
                         , bd::cpu_
                         , bs::saturated_tag
                         , bs::pack_<bd::uint_<A0>, X>
                         )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &, A0 const& a0) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( touint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    using result = bd::as_integer_t<A0, unsigned>;
    BOOST_FORCEINLINE result operator()(const saturated_tag &, const A0& a0) const BOOST_NOEXCEPT
    {
      using sr_t = bd::scalar_of_t<result>;
      static const A0 Vax = splat<A0>(bs::Valmax<sr_t>());
      return if_zero_else(bs::is_ngez(a0),
                          if_else(bs::is_greater_equal(a0, Vax), Valmax<result>(),
                                  touint(a0)
                                 )
                         );
    }
  };
} } }

#endif
