//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ULPDIST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ULPDIST_HPP_INCLUDED

#include <boost/simd/constant/eps.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/dist.hpp>
#include <boost/simd/function/ifrexp.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/ldexp.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/config.hpp>
#include <tuple>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( ulpdist_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::int_<A0> >
                          , bd::scalar_< bd::int_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return (a0>a1) ? saturated_(minus)(a0,a1) : saturated_(minus)(a1,a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ulpdist_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::uint_<A0> >
                          , bd::scalar_< bd::uint_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      return dist(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( ulpdist_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::floating_<A0> >
                          , bd::scalar_< bd::floating_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0>;

      if (a0 == a1)               return Zero<A0>();
      if (is_nan(a0)&&is_nan(a1)) return Zero<A0>();

      i_t e1, e2;
      A0 m1, m2;
      std::tie(m1, e1) = pedantic_(ifrexp)(a0);
      std::tie(m2, e2) = pedantic_(ifrexp)(a1);

      i_t expo = -simd::max(e1, e2);

      A0 e = (e1 == e2) ? simd::abs(m1-m2)
        :   simd::abs( simd::pedantic_(ldexp)(a0, expo)
                              - simd::pedantic_(ldexp)(a1, expo)
                            );
      return e/Eps<A0>();
    }
  };
} } }


#endif
