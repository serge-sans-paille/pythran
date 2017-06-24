//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_TANH_KERNEL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_TANH_KERNEL_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/horn1.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;
    template < typename A0, typename sA0 = bd::scalar_of_t<A0>>
    struct tanh_kernel;

    template < typename A0 >
    struct tanh_kernel < A0, float >
    {
      // computes tanh for abs(a0) < 0.625 and x2 =  sqr(a0) for float
      static BOOST_FORCEINLINE A0 tanh(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        return fma(horn<A0,
                   0XBEAAAA99, //    -3.33332819422E-1F
                   0X3E088393, //    +1.33314422036E-1F
                   0XBD5C1E2D, //    -5.37397155531E-2F
                   0X3CA9134E, //    +2.06390887954E-2F
                   0XBBBAF0EA  //    -5.70498872745E-3F
                   > (x2)*x2, a0, a0);
      }
      static BOOST_FORCEINLINE A0 coth(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        return rec(tanh(a0, x2));
      }
    };

    template < typename A0 >
    struct tanh_kernel < A0, double >
    {
      static  BOOST_FORCEINLINE A0 tanh(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        return fma(x2*p(x2)/q(x2), a0, a0);
      }
      static  BOOST_FORCEINLINE A0 coth(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        A0 qval =  q(x2);
        return qval/(a0*fma(p(x2), x2, qval));
      }

      // computes tanh for abs(a0) < 0.625 and x2 =  sqr(a0) for doubles
      static  BOOST_FORCEINLINE A0 p(const A0& x2) BOOST_NOEXCEPT
      {
        return horn<A0,
          0XC0993AC030580563ULL,// -1.61468768441708447952E3
          0XC058D26A0E26682DULL,// -9.92877231001918586564E1,
          0XBFEEDC5BAAFD6F4BULL // -9.64399179425052238628E-1
          > (x2);
      }
      static  BOOST_FORCEINLINE A0 q(const A0& x2)
      {
        return horn1<A0,
          0X40B2EC102442040CULL,   //  4.84406305325125486048E3
          0X40A176FA0E5535FAULL,   //  2.23548839060100448583E3,
          0X405C33F28A581B86ULL   //  1.12811678491632931402E2,
          //      0X3FF0000000000000ULL    //  1.0
          > (x2);
      }
    };
  }
} }
#endif
