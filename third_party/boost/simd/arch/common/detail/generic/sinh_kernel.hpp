//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_SINH_KERNEL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_SINH_KERNEL_HPP_INCLUDED
#include <boost/simd/function/horn.hpp>
#include <boost/simd/function/horn1.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < typename A0, typename sA0 = bd::scalar_of_t<A0>>
    struct sinh_kernel;

    template < typename A0 >
    struct sinh_kernel < A0, float >
    {
      // computes sinh for abs(a0) < 1 and x2 =  sqr(a0) for float
      static BOOST_FORCEINLINE A0 compute(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        return horn<A0,
          0x3f800000, // 1.0f
          0x3e2aaacc, // 1.66667160211E-1f
          0x3c087bbe, // 8.33028376239E-3f
          0x39559e2f  // 2.03721912945E-4f
          > (x2)*a0;
      }
    };

    template < typename A0 >
    struct sinh_kernel < A0, double >
    {
      // computes sinh for abs(a0) < 1 and x2 =  sqr(a0) for doubles
      static  BOOST_FORCEINLINE A0 compute(const A0& a0, const A0& x2) BOOST_NOEXCEPT
      {
        return fma(a0, (horn<A0,
                   0xc115782bdbf6ab05ull, //  -3.51754964808151394800E5
                   0xc0c694b8c71d6182ull, //  -1.15614435765005216044E4,
                   0xc064773a398ff4feull, //  -1.63725857525983828727E2,
                   0xbfe9435fe8bb3cd6ull  //  -7.89474443963537015605E-1
                   > (x2)/
          horn1<A0,
          0xc1401a20e4f90044ull, //  -2.11052978884890840399E6
          0x40e1a7ba7ed72245ull, //   3.61578279834431989373E4,
          0xc0715b6096e96484ull //  -2.77711081420602794433E2,
          //     0x3ff0000000000000ull  //   1.00000000000000000000E0
                   > (x2))*x2, a0);
      }
    };
  }
} }
#endif
