//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMQUO_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REMQUO_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <utility>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0)
                          , bd::cpu_
                          , bs::std_tag
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    using result_type = std::pair<A0,int>;

    BOOST_FORCEINLINE result_type operator() ( A0 a0, A0 a1
                                             ) const BOOST_NOEXCEPT
    {
      int q;
      A0 r = std::remquo(a0, a1, &q);
      return {r, q};
    }
  };

   BOOST_DISPATCH_OVERLOAD ( remquo_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_<bd::floating_<A0> >
                          , bd::scalar_<bd::floating_<A0> >
                          )
  {
    using quo_t = bd::as_integer_t<A0, signed>;
    using result_type = std::pair<A0,quo_t>;

    BOOST_FORCEINLINE std::pair<A0, quo_t> operator() ( A0 a0, A0 a1
                                      ) const BOOST_NOEXCEPT
    {
      A0 const d = nearbyint(a0/a1);

#if defined(BOOST_SIMD_NO_INVALIDS)
      A0  a2 = is_eqz(a1) ? Nan<A0>() : fma(-d, a1, a0);
#else
      A0  a2 = (is_invalid(a0) || is_eqz(a1)) ? Nan<A0>() : fma(-d, a1, a0);
#endif
      return {a2, toint(d)};
    }
  };
} } }


#endif
