//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_TRIG_EVALUATION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_TRIG_EVALUATION_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/horn1.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

//TODO some factoring with scalar
namespace boost { namespace simd { namespace detail
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  template <class A0> struct trig_evaluation < A0,  tag::simd_type, double>
  {
    typedef typename bd::as_integer<A0, signed>::type     iA0;
    typedef typename bd::scalar_of<A0>::type            stype;

    static BOOST_FORCEINLINE A0 cos_eval(const A0& z)
    {
      const A0 y = horn<A0,
        0x3fe0000000000000ll,
        0xbfa5555555555551ll,
        0x3f56c16c16c15d47ll,
        0xbefa01a019ddbcd9ll,
        0x3e927e4f8e06d9a5ll,
        0xbe21eea7c1e514d4ll,
        0x3da8ff831ad9b219ll
        > (z);
      return bs::oneminus(y*z);
    }

    static BOOST_FORCEINLINE A0 sin_eval(const A0& z, const A0& x)
    {
      const A0 y1 = horn<A0,
        0xbfc5555555555548ll,
        0x3f8111111110f7d0ll,
        0xbf2a01a019bfdf03ll,
        0x3ec71de3567d4896ll,
        0xbe5ae5e5a9291691ll,
        0x3de5d8fd1fcf0ec1ll
        > (z);
        return bs::fma(y1*z,x,x);
    }

    static BOOST_FORCEINLINE A0 base_tancot_eval(const A0& x)
    {
      const A0 zz = sqr(x);
      const A0 num = horn<A0,
        0xc1711fead3299176ll,
        0x413199eca5fc9dddll,
        0xc0c992d8d24f3f38ll
        >(zz);
      const A0 den = horn1<A0,
        0xc189afe03cbe5a31ll,
        0x4177d98fc2ead8efll,
        0xc13427bc582abc96ll,
        0x40cab8a5eeb36572ll
        //    0x3ff0000000000000ll
        >(zz);
      return fma(x, (zz*(num/den)), x);
    }

    template < typename A1>
    static BOOST_FORCEINLINE A0 tan_eval(const A0& z,  const A1& test)
    {
      A0 y = base_tancot_eval(z);
      return bs::if_else(test,y,-bs::rec(y));
    }
    template < typename A1>
    static BOOST_FORCEINLINE A0 cot_eval(const A0& z,  const A1& test)
    {
      A0 y = base_tancot_eval(z);
      return bs::if_else(test,bs::rec(y),-y);
    }
  };
} } }

#endif
