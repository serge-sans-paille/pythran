//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEXTAFTER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_NEXTAFTER_HPP_INCLUDED
#include <boost/simd/function/std.hpp>

#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/next.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/prev.hpp>
#include <boost/simd/function/sign.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd {
  namespace ext
  {
    namespace bd = boost::dispatch;
    BOOST_DISPATCH_OVERLOAD ( nextafter_
                            , (typename A0)
                            , bd::cpu_
                            , bd::scalar_< bd::floating_<A0> >
                            , bd::scalar_< bd::floating_<A0> >
                            )
    {
      BOOST_FORCEINLINE A0 operator() ( A0 x, A0 y) const BOOST_NOEXCEPT
      {
        return  (y >  x)  ? next(x) : ((y <  x) ?  prev(x) : x);
      }
    };
    BOOST_DISPATCH_OVERLOAD ( nextafter_
                            , (typename A0)
                            , bd::cpu_
                            , bd::scalar_< bd::arithmetic_<A0> >
                            , bd::scalar_< bd::arithmetic_<A0> >
                            )
    {
      BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
      {
        return a0+sign(a1-a0);
      }
    };
    BOOST_DISPATCH_OVERLOAD ( nextafter_
                            , (typename A0)
                            , bd::cpu_
                            , bd::scalar_< bd::unsigned_<A0> >
                            , bd::scalar_< bd::unsigned_<A0> >
                            )
    {
      BOOST_FORCEINLINE A0 operator() ( A0 a0, A0 a1) const BOOST_NOEXCEPT
      {
        return (a1 == a0) ? a0 : (a1 > a0) ? saturated_(inc)(a0) : saturated_(dec)(a0);
      }
    };
    BOOST_DISPATCH_OVERLOAD ( nextafter_
                            , (typename A0)
                            , bd::cpu_
                            , boost::simd::std_tag
                            , bd::scalar_< bd::floating_<A0> >
                            , bd::scalar_< bd::floating_<A0> >
                            )
    {
      BOOST_FORCEINLINE A0 operator() (const std_tag &, A0  a0, A0 a1
                                      ) const BOOST_NOEXCEPT
      {
        return std::nextafter(a0, a1);
      }
    };
    BOOST_DISPATCH_OVERLOAD ( nextafter_
                            , (typename A0)
                            , bd::cpu_
                            , boost::simd::std_tag
                            , bd::scalar_< bd::integer_<A0> >
                            , bd::scalar_< bd::integer_<A0> >
                            )
    {
      BOOST_FORCEINLINE A0 operator() (const std_tag &, A0  a0, A0 a1
                                      ) const BOOST_NOEXCEPT
      {
        return bs::nextafter(a0, a1);
      }
    };
  }
} }


#endif
