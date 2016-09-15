//==============================================================================
//          Copyright 2016   NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_GAMMA_KERNEL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_GAMMA_KERNEL_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;
    template < class A0, class sA0 = bd::scalar_of_t<A0> >
    struct gamma_kernel;

    template < class A0 >
    struct gamma_kernel < A0, float >
    {
      static BOOST_FORCEINLINE A0 gamma1(const A0& x)
      {
        return horn<A0,
                    0X3F800000UL, //  9.999999757445841E-01
                    0X3ED87799UL, //  4.227874605370421E-01
                    0X3ED2D411UL, //  4.117741948434743E-01
                    0X3DA82A34UL, //  8.211174403261340E-02
                    0X3D93AE7CUL, //  7.211014349068177E-02
                    0X3B91DB14UL, //  4.451165155708328E-03
                    0X3BA90C99UL, //  5.158972571345137E-03
                    0X3AD28B22UL  //  1.606319369134976E-03
                    > (x);
      }

    };

    template < class A0 >
    struct gamma_kernel < A0, double >
    {
      static BOOST_FORCEINLINE A0 gamma1(const A0& x)
      {
        return
    horn<A0,
         0X3FF0000000000000ULL, // 9.99999999999999996796E-1
         0X3FDFA1373993E312ULL, // 4.94214826801497100753E-1
         0X3FCA8DA9DCAE7D31ULL, // 2.07448227648435975150E-1
         0X3FA863D918C423D3ULL, // 4.76367800457137231464E-2
         0X3F8557CDE9DB14B0ULL, // 1.04213797561761569935E-2
         0X3F5384E3E686BFABULL, // 1.19135147006586384913E-3
         0X3F24FCB839982153ULL  // 1.60119522476751861407E-4
         > (x)/
      horn<A0,
           0X3FF0000000000000ULL, //  1.00000000000000000320E00
           0X3FB24944C9CD3C51ULL, //  7.14304917030273074085E-2
           0XBFCE071A9D4287C2ULL, // -2.34591795718243348568E-1
           0X3FA25779E33FDE67ULL, //  3.58236398605498653373E-2
           0X3F8831ED5B1BB117ULL, //  1.18139785222060435552E-2
           0XBF7240E4E750B44AULL, // -4.45641913851797240494E-3
           0X3F41AE8A29152573ULL, //  5.39605580493303397842E-4
           0XBEF8487A8400D3AFULL  // -2.31581873324120129819E-5
           > (x);

      }
    };
  }
} }
#endif
