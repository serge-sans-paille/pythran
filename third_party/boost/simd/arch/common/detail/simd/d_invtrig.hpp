//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_INVTRIG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_INVTRIG_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/horn1.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/constant/sqrteps.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/fms.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/if_zero_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0 >
    struct invtrig_base<A0,tag::radian_tag,tag::simd_type, double>
    {
      static BOOST_FORCEINLINE A0 asin(const A0& a0)
      {
        A0 x = bs::abs(a0);
        auto small_=  bs::is_less(x, bs::Sqrteps<A0>());
        const A0 ct1 = Constant<A0, 0x3fe4000000000000ll>();
        A0 zz1 = bs::oneminus(x);
        const A0 vp = zz1*horn<A0,
          0x403c896240f3081dll,
          0xc03991aaac01ab68ll,
          0x401bdff5baf33e6all,
          0xbfe2079259f9290fll,
          0x3f684fc3988e9f08ll
          >(zz1)/
          horn1<A0,
          0x40756709b0b644bell,
          0xc077fe08959063eell,
          0x40626219af6a7f42ll,
          0xc035f2a2b6bf5d8cll
          >(zz1);
        zz1 =  bs::sqrt(zz1+zz1);
        A0 z = bs::Pio_4<A0>()-zz1;
        zz1 = fms(zz1, vp, Pio_2lo<A0>());
        z =  z-zz1;
        zz1 = z+bs::Pio_4<A0>();
        A0 zz2 = bs::sqr(a0);
        z = zz2*horn<A0,
          0xc020656c06ceafd5ll,
          0x40339007da779259ll,
          0xc0304331de27907bll,
          0x4015c74b178a2dd9ll,
          0xbfe34341333e5c16ll,
          0x3f716b9b0bd48ad3ll
          >(zz2)/
          horn1<A0,
          0xc04898220a3607acll,
          0x4061705684ffbf9dll,
          0xc06265bb6d3576d7ll,
          0x40519fc025fe9054ll,
          0xc02d7b590b5e0eabll
          >(zz2);
        zz2 = x*z+x;
        return bs::if_nan_else(bs::is_greater(x,bs::One<A0>()),
                               bs::bitwise_xor(bs::if_else( small_,
                                                            x,
                                                            bs::if_else(x > ct1, zz1, zz2)
                                                          )
                                              , bs::bitofsign(a0)
                                              )
                              );
      }

      static BOOST_FORCEINLINE A0 acos(const A0& a0)
      {
        A0 x = bs::abs(a0);
        auto x_larger_05 = x > bs::Half<A0>();
        x  = if_else(x_larger_05, bs::sqrt(fma(bs::Mhalf<A0>(), x, bs::Half<A0>())), a0);
        x  = asin(x);
        x =  if_plus(x_larger_05, x, x);
        x  = bs::if_else(is_less(a0, bs::Mhalf<A0>()), bs::Pi<A0>()-x, x);
        return bs::if_else(x_larger_05, x, bs::Pio_2<A0>()-x);
      }

      static BOOST_FORCEINLINE A0 atan(const A0& a0)
      {
        A0 absa0 =  bs::abs(a0);
        const A0 x  = kernel_atan(absa0, bs::rec(absa0));
        return bs::bitwise_xor(x, bs::bitofsign(a0));
      }

      static BOOST_FORCEINLINE A0 acot(const A0& a0)
      {
        A0 absa0 =  bs::abs(a0);
        const A0 x  = kernel_atan(bs::rec(absa0), absa0);
        return bs::bitwise_xor(x, bs::bitofsign(a0));
      }

      static BOOST_FORCEINLINE A0 kernel_atan(const A0& x, const A0& recx)
      {
        auto flag1 = bs::is_less(x,  Tan_3pio_8<A0>());
        auto flag2 = bs::logical_and(x >= Tanpio_8<A0>(), flag1);
        A0 yy = bs::if_zero_else(flag1, bs::Pio_2<A0>());
        yy = bs::if_else(flag2, bs::Pio_4<A0>(), yy);
        A0 xx = bs::if_else(flag1, x, -recx);
        xx = bs::if_else(flag2, bs::dec(x)/bs::inc(x),xx);
        A0 z = bs::sqr(xx);
        z *= horn<A0,
          0xc0503669fd28ec8ell,
          0xc05eb8bf2d05ba25ll,
          0xc052c08c36880273ll,
          0xc03028545b6b807all,
          0xbfec007fa1f72594ll
          >(z)/
          horn1<A0,
          0x4068519efbbd62ecll,
          0x407e563f13b049eall,
          0x407b0e18d2e2be3bll,
          0x4064a0dd43b8fa25ll,
          0x4038dbc45b14603cll
          >(z);
        z = bs::fma(xx, z, xx);
        z = bs::if_plus(flag2, z, Pio_4lo<A0>());
        z = z+bs::if_zero_else(flag1, Pio_2lo<A0>());
        return yy + z;
      }
    };
  }
} }
#endif
