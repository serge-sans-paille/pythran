//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOINT_S_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_TOINT_S_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_less_equal.hpp>
#include <boost/simd/function/saturate.hpp>
#include <boost/simd/function/splat.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/constant/valmax.hpp>
#include <boost/simd/constant/valmin.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_nan.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( toint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::uint_<A0>, X>
                            )
  {
    using result = bd::as_integer_t<A0, signed>;
    BOOST_FORCEINLINE result operator()(const saturated_tag &, A0 const& a0) const
    {
      return bitwise_cast<result>(saturate<result>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD( toint_
                            , (typename A0, typename X)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::int_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const saturated_tag &, A0 const& a0) const
    {
      return a0;
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( toint_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::saturated_tag
                            , bs::pack_<bd::floating_<A0>, X>
                            )
  {
    using result = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE result operator()(const saturated_tag &
                                       ,  const A0& a0) const BOOST_NOEXCEPT
    {
      using sr_t = bd::scalar_of_t<result>;
      const A0 Vax = A0(bs::Valmax<sr_t>());
      const A0 Vix = A0(bs::Valmin<sr_t>());
    #ifndef BOOST_SIMD_NO_NANS
      A0 aa0 = if_zero_else(is_nan(a0), a0);
      return if_else(bs::is_less_equal(aa0, Vix), Valmin<result>(),
                     if_else(bs::is_greater_equal(aa0, Vax), Valmax<result>(),
                             pedantic_(toint)(aa0)
                            )
                    );
    #else
      return if_else(bs::is_less_equal(a0, Vix), Valmin<result>(),
                     if_else(bs::is_greater_equal(a0, Vax), Valmax<result>(),
                              pedantic_(toint)(a0)
                            )
                    );
    #endif
    }
  };
} } }

#endif
