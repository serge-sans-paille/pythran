//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_DETAIL_SCALAR_D_EXPO_REDUCTION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_DETAIL_SCALAR_D_EXPO_REDUCTION_HPP_INCLUDED

#include <boost/simd/arch/detail/scalar/horner.hpp>
#include <boost/simd/constant/invlog10_2.hpp>
#include <boost/simd/constant/invlog_2.hpp>
#include <boost/simd/detail/constant/log10_2hi.hpp>
#include <boost/simd/detail/constant/log10_2lo.hpp>
#include <boost/simd/constant/log_10.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/detail/constant/maxlog10.hpp>
#include <boost/simd/detail/constant/maxlog2.hpp>
#include <boost/simd/detail/constant/minlog.hpp>
#include <boost/simd/detail/constant/minlog10.hpp>
#include <boost/simd/detail/constant/minlog2.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/fnms.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/oneminus.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0> struct exp_reduction < A0, natural_tag, double>
    {
      using l_t = logical<A0>;
      static BOOST_FORCEINLINE l_t isgemaxlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 >= Maxlog<A0>());
      }

      static BOOST_FORCEINLINE l_t isleminlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 <= Minlog<A0>());
      }

      static BOOST_FORCEINLINE A0 reduce( A0 a0
                                        , A0& hi, A0& lo, A0& x) BOOST_NOEXCEPT
      {
        A0 k = nearbyint(Invlog_2<A0>()*a0);
        hi = fnms(k, Log_2hi<A0>(), a0); //a0-k*L
        lo = k*Log_2lo<A0>();
        x  = hi-lo;
        return k;
      }

      static BOOST_FORCEINLINE A0 approx(A0 x) BOOST_NOEXCEPT
      {
        A0 const t = sqr(x);
        return fnms(t, horner<BOOST_SIMD_HORNER_COEFF_T(A0, 5,
                                                        ( 0x3e66376972bea4d0ull
                                                        , 0xbebbbd41c5d26bf1ull
                                                        , 0x3f11566aaf25de2cull
                                                        , 0xbf66c16c16bebd93ull
                                                        , 0x3fc555555555553eull
                                                        )
                                                       )>(t), x); //x-h*t
      }

      static BOOST_FORCEINLINE A0 finalize(A0 x, A0 c, A0 hi, A0 lo) BOOST_NOEXCEPT
      {
        return oneminus(((lo-(x*c)/(Two<A0>()-c))-hi));
      }

    };

    template < class A0 > struct exp_reduction < A0, two_tag, double>
    {
      using l_t = logical<A0>;
      static BOOST_FORCEINLINE l_t isgemaxlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 >= Maxlog2<A0>());
      }

      static BOOST_FORCEINLINE l_t isleminlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 <= Minlog2<A0>());
      }

      static BOOST_FORCEINLINE A0 reduce(A0 a0, A0, A0, A0& x) BOOST_NOEXCEPT
      {
        A0 k = nearbyint(a0);
        x = (a0 - k)*Log_2<A0>();
        return k;
      }

      static BOOST_FORCEINLINE A0 approx(A0 x) BOOST_NOEXCEPT
      {
        const A0 t =  sqr(x);
        return fnms(t, horner<BOOST_SIMD_HORNER_COEFF_T(A0, 5,
                                                        ( 0x3e66376972bea4d0ull
                                                        , 0xbebbbd41c5d26bf1ull
                                                        , 0x3f11566aaf25de2cull
                                                        , 0xbf66c16c16bebd93ull
                                                        , 0x3fc555555555553eull
                                                        )
                                                       )> (t), x); //x-h*t
      }

      static BOOST_FORCEINLINE A0 finalize( A0 x, A0 c, A0, A0& ) BOOST_NOEXCEPT
      {
        return oneminus(((-(x*c)/(Two<A0>()-c))-x));
      }
    };

    template < class A0 > struct exp_reduction < A0, ten_tag, double>
    {
      using l_t = logical<A0>;
      static BOOST_FORCEINLINE l_t isgemaxlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 >= Maxlog10<A0>());
      }

      static BOOST_FORCEINLINE l_t isleminlog(A0 a0) BOOST_NOEXCEPT
      {
        return (a0 <= Minlog10<A0>());
      }

      static BOOST_FORCEINLINE A0 reduce(A0 a0, A0&, A0&, A0& x) BOOST_NOEXCEPT
      {
        A0 k  = nearbyint(Invlog10_2<A0>()*a0);
        x = fnms(k, Log10_2hi<A0>(), a0);
        x = fnms(k, Log10_2lo<A0>(), x);
        return k;
      }

      static BOOST_FORCEINLINE A0 approx(A0 x) BOOST_NOEXCEPT
      {
        A0 xx = sqr(x);
        A0 px = x*horner<BOOST_SIMD_HORNER_COEFF_T(A0, 4,
                                                   (0x3fa4fd75f3062dd4ull,
                                                    0x40277d9474c55934ull,
                                                    0x40796b7a050349e4ull,
                                                    0x40a2b4798e134a01ull)
                                                  )> (xx);
        A0 x2 =  px/(horner<BOOST_SIMD_HORNER_COEFF_T(A0, 4,
                                                      (0x3ff0000000000000ull,
                                                       0x405545fdce51ca08ull,
                                                       0x4093e05eefd67782ull,
                                                       0x40a03f37650df6e2ull)
                                                     )> (xx)-px);
        return inc(x2+x2);
      }

      static BOOST_FORCEINLINE A0 finalize(A0, A0 c, A0,  A0 ) BOOST_NOEXCEPT
      {
        return c;
      }
    };
  }
} }
#endif
