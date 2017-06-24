//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_INVTRIG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_F_INVTRIG_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/mhalf.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/detail/constant/pio_2lo.hpp>
#include <boost/simd/constant/pio_3.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/detail/constant/pio_4lo.hpp>
#include <boost/simd/constant/tan_3pio_8.hpp>
#include <boost/simd/constant/tanpio_8.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/twopio_3.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/ifnot_plus.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/oneminus.hpp>
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
  struct invtrig_base<A0,tag::radian_tag,tag::simd_type, float>
  {
    static BOOST_FORCEINLINE A0 asin(A0 const& a0)
    {
      A0 sgn, x;
      x = bs::abs(a0);
      sgn = bs::bitofsign(a0);
      const auto x_larger_05 = x > bs::Half<A0>();
      A0 z = if_else(x_larger_05, bs::Half<A0>()*bs::oneminus(x), bs::sqr(x));
      x = if_else(x_larger_05, sqrt(z), x);
      // Remez polynomial of degree 4 for (asin(rx)-rx)/(rx*rx*rx) in [0, 0.25]
      // 2120752146 values (99.53%) within 0.0 ULPs
      //    9954286 values (0.47%)  within 0.5 ULPs
      // 4.0 cycles/element SSE4.2 g++-4.8
      A0 z1 = horn<A0,
        0x3e2aaae4,
        0x3d9980f6,
        0x3d3a3ec7,
        0x3cc617e3,
        0x3d2cb352
        > (z);
      z1 = bs::fma(z1, z*x, x);
      z = if_else(x_larger_05, bs::Pio_2<A0>()-(z1+z1), z1);
      return bs::bitwise_xor(z, sgn);
    }

    static BOOST_FORCEINLINE A0 acos(const A0& a0)
    {
      // 2130706432 values computed.
      // 1968272987 values (92.38%) within 0.0 ULPs
      //  162433445 values (7.62%)  within 0.5 ULPs
      // 8.5 cycles/element SSE4.2 g++-4.8
      A0 x = bs::abs(a0);
      auto x_larger_05 = is_greater(x, bs::Half<A0>());
      x  = if_else(x_larger_05, bs::sqrt(fma(bs::Mhalf<A0>(), x, bs::Half<A0>())), a0);
      x  = asin(x);
      x =  if_plus(x_larger_05, x, x);
      x  = bs::if_else(a0 < bs::Mhalf<A0>(), bs::Pi<A0>()-x, x);
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

    static BOOST_FORCEINLINE A0 kernel_atan(const A0&  x, const A0& recx)
    {
      //4278190076 values computed  in range: [-3.40282e+38, 3.40282e+38]
      //4257598358 values (99.52%)  within 0.0 ULPs
      //  20591718 values (0.48%)   within 0.5 ULPs

      //here x is positive
      const auto flag1 = x < Tan_3pio_8<A0>();
      const auto flag2 = bs::logical_and(x >= Constant<A0, 0x3ed413cd>(), flag1);
      A0 yy =  bs::if_zero_else(flag1, Pio_2<A0>());
      yy =  bs::if_else(flag2, Pio_4<A0>(), yy);
      A0 xx =   bs::if_else(flag1, x, -recx);
      xx =  bs::if_else(flag2, (bs::dec(x)/bs::inc(x)),xx);
      const A0 z = bs::sqr(xx);
      A0 z1 = horn<A0
        , 0xbeaaaa2aul  // -3.3333293e-01
        , 0x3e4c925ful  //  1.9991724e-01
        , 0xbe0e1b85ul  // -1.4031009e-01
        , 0x3da4f0d1ul  //  8.5460119e-02
        > (z);
      z1 = bs::fma(xx, bs::multiplies( z1, z), xx);
      z1 = if_plus(flag2, z1, Pio_4lo<A0>());
      z1 = ifnot_plus(flag1, z1, Pio_2lo<A0>());
      return yy+z1;
    }
  };
}
} }
#endif
