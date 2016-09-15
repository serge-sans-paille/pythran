//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_D_INVTRIG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SCALAR_D_INVTRIG_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/horn1.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
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
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0 >
    struct invtrig_base<A0,tag::radian_tag,tag::not_simd_type, double>
    {
      static BOOST_FORCEINLINE A0 asin(A0 a0) BOOST_NOEXCEPT
      {
        A0 x = bs::abs(a0);
        if ((x >  One<A0>())) return Nan<A0>();
        if ((x <  Sqrteps<A0>())) return a0;
        A0 zz;
        if((x >  Constant<double,0x3fe4000000000000ull> ())) //0.625;
        {
          zz = oneminus(x);
          const A0 vp = zz*horn<A0,
                                0x403c896240f3081dll,
                                0xc03991aaac01ab68ll,
                                0x401bdff5baf33e6all,
                                0xbfe2079259f9290fll,
                                0x3f684fc3988e9f08ll
                                >(zz)/
                    horn1<A0,
                         0x40756709b0b644bell,
                         0xc077fe08959063eell,
                         0x40626219af6a7f42ll,
                         0xc035f2a2b6bf5d8cll
                         >(zz);
          zz = sqrt(zz+zz);
          A0 z = Pio_4<A0>()-zz;
          zz = fma(zz, vp, Pio_2lo<A0>());
          z =  z-zz;
          zz = z+Pio_4<A0>();
        }
        else
        {
          zz = sqr(x);
          A0 z = zz*horn<A0,
                         0xc020656c06ceafd5ll,
                         0x40339007da779259ll,
                         0xc0304331de27907bll,
                         0x4015c74b178a2dd9ll,
                         0xbfe34341333e5c16ll,
                         0x3f716b9b0bd48ad3ll
                         >(zz)/
                  horn1<A0,
                       0xc04898220a3607acll,
                       0x4061705684ffbf9dll,
                       0xc06265bb6d3576d7ll,
                       0x40519fc025fe9054ll,
                       0xc02d7b590b5e0eabll
                       >(zz);
          zz = x*z+x;
      }
        return bitwise_xor(bitofsign(a0), zz);
      }

      static BOOST_FORCEINLINE A0 acos(A0 a0) BOOST_NOEXCEPT
      {
        if ((abs(a0) > One<A0>())) return Nan<A0>();
        if( a0 > Half<A0>() )
        {
          return Two<A0>() * asin(  sqrt(fma(Mhalf<A0>(), a0, Half<A0>()) )) ;
        }
        A0 z = Pio_4<A0>() - asin(a0);
        z = z + Pio_4lo<A0>();
        z = z + Pio_4<A0>();
        return z;
      }

      static BOOST_FORCEINLINE A0 atan(A0 a0) BOOST_NOEXCEPT
      {
        A0 x  = abs(a0);
        return bitwise_xor(kernel_atan(x, rec(x)), bitofsign(a0));
      }

      static BOOST_FORCEINLINE A0 acot(A0 a0) BOOST_NOEXCEPT
      {
        A0 x  = abs(a0);
        return bitwise_xor(kernel_atan(rec(x), x), bitofsign(a0));
      }

      static BOOST_FORCEINLINE A0 kernel_atan(A0 x, A0 recx) BOOST_NOEXCEPT
      {
        if (is_eqz(x)) return Zero<A0>();
        if (x == Inf<A0>()) return Pio_2<A0>();
        A0 y;
        A0 flag = (x > Tan_3pio_8<A0>());
        if (flag)
        {
          y =  Pio_2<A0>();
          x =  -recx;
        }
        else if ((x <=  Constant<double,0x3fe51eb851eb851full>())) //0.66
        {
          y = Zero<A0>();
        }
        else
        {
          y = Pio_4<A0>();
          flag = Half<A0>();
          x = dec(x)/inc(x);
        }
        A0 z = sqr(x);
        z = z*horn<A0,
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
          //   0x3ff0000000000000ll
                     >(z);
        z = fma(x, z, x);
        z += flag * Pio_2lo<A0>();
        return y + z;
      }


    };
  }
} }
#endif
