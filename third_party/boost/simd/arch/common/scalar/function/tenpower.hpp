//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TENPOWER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_TENPOWER_HPP_INCLUDED

#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/ten.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_odd.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/config.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( tenpower_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    using result_t = bd::as_floating_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 expo) const BOOST_NOEXCEPT
    {

      result_t result = One<result_t>();
      result_t base = Ten<result_t>();
      auto neg = is_ltz(expo);
      expo =  boost::simd::abs(expo);
      while(expo)
      {
        if (is_odd(expo)) result *= base;
        expo >>= 1;
        base = sqr(base);
      }
      return neg ? rec(result) : result;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( tenpower_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint_<A0> >
                          )
  {
    using result_t = bd::as_floating_t<A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 expo) const BOOST_NOEXCEPT
    {
      result_t result = One<result_t>();
      result_t base = Ten<result_t>();
      while(expo)
      {
        if (is_odd(expo)) result *= base;
        expo >>= 1;
        base = sqr(base);
      }
      return result;
    }
  };
} } }


#endif
