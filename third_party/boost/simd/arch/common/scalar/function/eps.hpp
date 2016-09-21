//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EPS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_EPS_HPP_INCLUDED

#include <boost/simd/constant/mindenormal.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/nbmantissabits.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/exponent.hpp>
#include <boost/simd/function/is_invalid.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( eps_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::arithmetic_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator()( A0 ) const BOOST_NOEXCEPT
    {
      return One<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( eps_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    A0 operator() ( A0 a0) const BOOST_NOEXCEPT
    {
      typedef std::numeric_limits<A0> lim;
      const A0 a = bs::abs(a0);
      if (is_invalid(a))
      {
        return Nan<A0>();
      }
      else if (a < lim::min())
      {
        return Mindenormal<A0>();
      }
      else
      {
        using i_t = bd::as_integer_t<A0, unsigned>;
        i_t e1 = exponent(a)-lim::digits+1;
        return bitwise_cast<A0>(bitwise_cast<i_t>(One<A0>())+(e1 << Nbmantissabits<A0>()));
      }
    }
  };
} } }


#endif
