//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_F_EXPO_REDUCTION_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_GENERIC_F_EXPO_REDUCTION_HPP_INCLUDED

#include <boost/simd/function/horn.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
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
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/is_less_equal.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/fnms.hpp>
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

    template<class A0> struct exp_reduction <A0,bs::tag::exp_,float>
    {
      static BOOST_FORCEINLINE auto isgemaxlog(A0 const& a0) BOOST_NOEXCEPT
        -> decltype(is_greater_equal(a0, Maxlog<A0>()))
      {
        return is_greater_equal(a0, Maxlog<A0>());
      }

      static BOOST_FORCEINLINE auto isleminlog(A0 const& a0) BOOST_NOEXCEPT
       -> decltype(is_less_equal(a0, Minlog<A0>()))
      {
        return is_less_equal(a0, Minlog<A0>());
      }

      static BOOST_FORCEINLINE A0 approx(A0 const& x) BOOST_NOEXCEPT
      {
        // Remez polynomial of degree 4 on [-0.5 0.5] for (exp(x)-1-x)/sqr(x)
        // tested in range: [-88.3763, 88.3763]
        //2214928753 values (98.98%)  within 0.0 ULPs
        //  22831063 values (1.02%)   within 0.5 ULPs
        //  4.89648 cycles/value (SSE4.2 g++-4.8)
        A0 y = horn<A0,
                    0x3f000000, //  5.0000000e-01
                    0x3e2aa9a5, //  1.6666277e-01
                    0x3d2aa957, //  4.1665401e-02
                    0x3c098d8b, //  8.3955629e-03
                    0x3ab778cf  //  1.3997796e-03
                    >(x);
        return inc(fma(y, sqr(x), x));
      }

      static BOOST_FORCEINLINE A0 reduce(A0 const& a0, A0& x) BOOST_NOEXCEPT
      {
        A0 k = nearbyint(Invlog_2<A0>()*a0);
        x = fnms(k, Log_2hi<A0>(), a0); //a0-k*L
        x = fnms(k, Log_2lo<A0>(), x);
        return k;
      }
    };

    template < class A0 > struct exp_reduction < A0, bs::tag::exp2_, float>
    {
     static BOOST_FORCEINLINE auto isgemaxlog(A0 const& a0) BOOST_NOEXCEPT
        -> decltype(is_greater_equal(a0, Maxlog2<A0>()))
      {
        return is_greater_equal(a0, Maxlog2<A0>());
      }

      static BOOST_FORCEINLINE auto isleminlog(A0 const& a0) BOOST_NOEXCEPT
        -> decltype(is_less_equal(a0, Minlog2<A0>()))
      {
        return is_less_equal(a0, Minlog2<A0>());
      }

      static BOOST_FORCEINLINE A0 approx(A0 const& x) BOOST_NOEXCEPT
      {
        // Remez polynom of degree 4 on [-0.5, 0.5] for (exp2(x)-1-x*log(2))/sqr(x)  tested in range: [-127 127]
        // 2247884800 values computed.
        // 2224606419 values (98.96%)  within 0.0 ULPs
        // 23278381 values (1.04%)   within 0.5 ULPs
        // 3.5 cycles/value  (SSE4.2 g++-4.8)
        A0 y = horn<A0,
                    0x3e75fdf1,  //    2.4022652e-01
                    0x3d6356eb,  //    5.5502813e-02
                    0x3c1d9422,  //    9.6178371e-03
                    0x3ab01218,  //    1.3433127e-03
                    0x3922c8c4   //    1.5524315e-04
                    >(x);
      return inc(fma(y, sqr(x), x*Log_2<A0>()));
      }

      static BOOST_FORCEINLINE A0 reduce( A0 const& a0, A0& x) BOOST_NOEXCEPT
      {
        A0 k = nearbyint(a0);
        x = (a0 - k);
        return k;
      }
    };

    template < class A0 > struct exp_reduction < A0, bs::tag::exp10_, float>
    {
      static BOOST_FORCEINLINE auto isgemaxlog(A0 const& a0) BOOST_NOEXCEPT
        -> decltype(is_greater_equal(a0, Maxlog10<A0>()))
      {
        return is_greater_equal(a0, Maxlog10<A0>());
      }

      static BOOST_FORCEINLINE auto isleminlog(A0 const& a0) BOOST_NOEXCEPT
        -> decltype(is_less_equal(a0, Minlog10<A0>()))
      {
        return is_less_equal(a0, Minlog10<A0>());
      }

      static BOOST_FORCEINLINE A0 reduce(A0 const& a0, A0& x) BOOST_NOEXCEPT
      {
        A0 k = nearbyint(Invlog10_2<A0>()*a0);
        x = fnms(k, Log10_2hi<A0>(), a0);
        x -= k*Log10_2lo<A0>();
        return k;
      }

      static BOOST_FORCEINLINE A0 approx(A0 const& x) BOOST_NOEXCEPT
      {
        // Remez polynom of degree 5 on [-0.5, 0.5]*log10(2) for (exp10(x)-1)/x   tested in range: [-37.9, 38.2308]
        //  2217772528 values computed.
        //  2198853506 values (99.15%)  within 0.0 ULPs
        //  18919022 values (0.85%)   within 0.5 ULPs
        //      5.2 cycles/value  (SSE4.2 g++-4.8)
        return inc(horn<A0,
                        0x40135d8e, //    2.3025851e+00
                        0x4029a926, //    2.6509490e+00
                        0x400237da, //    2.0346589e+00
                        0x3f95eb4c, //    1.1712432e+00
                        0x3f0aacef, //    5.4170126e-01
                        0x3e54dff1  //    2.0788552e-01
                        >(x)*x);
    }
  };
}
} }
#endif
