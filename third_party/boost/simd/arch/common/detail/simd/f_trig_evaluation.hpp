//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_TRIG_EVALUATION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_TRIG_EVALUATION_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  template <class A0> struct trig_evaluation < A0,  tag::simd_type, float>
  {
    typedef typename bd::as_integer<A0, signed>::type          iA0;
    typedef typename bd::scalar_of<A0>::type                 stype;

    static BOOST_FORCEINLINE A0 cos_eval(const A0& z)
    {
      const A0 y = bs::horn<A0
        , 0x3d2aaaa5
        , 0xbab60619
        , 0x37ccf5ce > (z);
      return bs::inc(bs::fma(z,bs::Mhalf<A0>(), y*bs::sqr(z)));
    }

    static BOOST_FORCEINLINE A0 sin_eval(const A0& z, const A0& x)
    {
      const A0 y1 =  bs::horn< A0
        , 0xbe2aaaa2
        , 0x3c08839d
        , 0xb94ca1f9 > (z);
      return bs::fma(bs::multiplies(y1,z),x,x);
    }

    static BOOST_FORCEINLINE A0 base_tancot_eval(const A0& z)
    {
      const A0 zz = bs::sqr(z);
      return fma(bs::horn<A0
                , 0x3eaaaa6f
                , 0x3e0896dd
                , 0x3d5ac5c9
                , 0x3cc821b5
                , 0x3b4c779c
                , 0x3c19c53b>(zz), zz*z, z);
    }
    template <class A1>
    static BOOST_FORCEINLINE A0 tan_eval(const A0& z,  const A1& test)
    {
      A0 y = base_tancot_eval(z);
      return bs::if_else(test,y,-bs::rec(y));
    }
    template <class A1>
    static BOOST_FORCEINLINE A0 cot_eval(const A0& z,  const A1& test)
    {
      A0 y = base_tancot_eval(z);
      return bs::if_else(test,bs::rec(y),-y);
    }
  };
} } }

#endif
