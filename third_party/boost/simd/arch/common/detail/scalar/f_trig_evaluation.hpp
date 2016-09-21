//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_F_TRIG_EVALUATION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_F_TRIG_EVALUATION_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0,
               class style,
               class base_A0 = bd::scalar_of_t<A0>
             >
    struct trig_evaluation {};

    // This class exposes the public static members:
    // sin_eval
    // cos_eval
    // tan_eval
    // which evaluate a polynomial approximation of each standard trigonometric
    // functions in the range [pi/4, -pi/4]


    template < class A0> struct trig_evaluation < A0,  tag::not_simd_type, float>
    {
      static BOOST_FORCEINLINE A0 cos_eval(A0 z) BOOST_NOEXCEPT
      {
        const A0 y = horn<A0
          , 0x3d2aaaa5
          , 0xbab60619
          , 0x37ccf5ce
          > (z);
        return inc( fma(z,Mhalf<A0>(), y* sqr(z)));
      }

      static BOOST_FORCEINLINE A0 sin_eval(A0 z, A0 x) BOOST_NOEXCEPT
      {
        const A0 y1 = horn<A0
          , 0xbe2aaaa2
          , 0x3c08839d
          , 0xb94ca1f9
          > (z);
        return fma(y1*z,x,x);
      }

      static BOOST_FORCEINLINE A0 base_tan_eval(A0 z) BOOST_NOEXCEPT
      {
        const A0 zz = sqr(z);
        A0 y = horn<A0,
          0x3eaaaa6f,
          0x3e0896dd,
          0x3d5ac5c9,
          0x3cc821b5,
          0x3b4c779c,
          0x3c19c53b
          >(zz)*zz*z+z;
        return y;
      }

      static BOOST_FORCEINLINE A0 tan_eval(A0 z, const int n) BOOST_NOEXCEPT
      {
        const A0 y = base_tan_eval(z);
        if (n == 1) return y;  else return -rec(y);
      }
      static BOOST_FORCEINLINE A0 cot_eval(A0 z, const int n) BOOST_NOEXCEPT
      {
        const A0 y = base_tan_eval(z);
        if (n == 1) return rec(y);  else return -y;
      }
    };
  }
} }
#endif
