//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_HYPOT_HPP_INCLUDED
#include <boost/simd/function/pedantic.hpp>


#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/is_nan.hpp>
#endif
#include <boost/simd/detail/constant/maxexponentm1.hpp>
#include <boost/simd/detail/constant/minexponent.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/std.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( hypot_
                          , (typename A0)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const pedantic_tag &,
                                     A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;
      #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0) && is_inf(a1)) return Inf<A0>();
      if (is_inf(a0) && is_nan(a1)) return Inf<A0>();
      #endif
      A0 r =  bs::abs(a0);
      A0 i =  bs::abs(a1);
      i_t e =  exponent(bs::max(i, r));
      e = bs::min(bs::max(e,Minexponent<A0>()),Maxexponentm1<A0>());
      return bs::pedantic_(ldexp)(sqrt(sqr(bs::pedantic_(ldexp)(r, -e))
                                       +sqr(bs::pedantic_(ldexp)(i, -e))), e);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( hypot_
                          , (typename A0)
                          , bd::cpu_
                          , boost::simd::std_tag
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() (const std_tag &,  A0 a0, A0 a1
                                    ) const BOOST_NOEXCEPT
    {
      return std::hypot(a0, a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( hypot_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {

    BOOST_FORCEINLINE A0 operator() ( A0  a0, A0  a1
                                    ) const BOOST_NOEXCEPT
    {
      return boost::simd::sqrt(bs::fma(a0, a0, sqr(a1)));
    }
  };
} } }


#endif
