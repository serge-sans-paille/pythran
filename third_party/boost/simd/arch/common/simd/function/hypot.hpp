//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_HYPOT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/detail/constant/minexponent.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/predef/architecture.h>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/constant/inf.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF(hypot_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()(const pedantic_tag &,
                                      const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using iA0 = bd::as_integer_t<A0>;
        A0 r =  bs::abs(a0);
        A0 i =  bs::abs(a1);
        iA0 e =  exponent(bs::max(i, r));
        e = bs::min(bs::max(e,Minexponent<A0>()),Maxexponentm1<A0>());
        A0 res =  pedantic_(ldexp)(sqrt(sqr(pedantic_(ldexp)(r, -e))
                                        +sqr(pedantic_(ldexp)(i, -e))), e);

        #ifndef BOOST_SIMD_NO_INVALIDS
        auto test = logical_or(logical_and(is_nan(a0), is_inf(a1)),
                              logical_and(is_nan(a1), is_inf(a0)));
        auto v = if_else(test, Inf<A0>(), res);
        return v;
        #else
        return res;
        #endif
      }
   };

  BOOST_DISPATCH_OVERLOAD_IF ( hypot_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
  {

    BOOST_FORCEINLINE A0 operator() (A0 const& a0, A0 const& a1
                                    ) const BOOST_NOEXCEPT
    {
      return boost::simd::sqrt(bs::fma(a0, a0, sqr(a1)));
    }
  };
} } }

#endif

