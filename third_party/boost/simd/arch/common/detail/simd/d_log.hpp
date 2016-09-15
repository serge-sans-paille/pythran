//==================================================================================================
/*!

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_LOG_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_DETAIL_SIMD_D_LOG_HPP_INCLUDED


#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/tofloat.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/frexp.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/constant/invlog_2.hpp>
#include <boost/simd/constant/invlog_10.hpp>
#include <boost/simd/constant/log_2olog_10.hpp>
#include <boost/simd/detail/constant/log_2hi.hpp>
#include <boost/simd/detail/constant/log_2lo.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/sqrt_2o_2.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>
#include <tuple>

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/is_nan.hpp>
#endif
#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#endif

namespace boost { namespace simd
{
  namespace detail
  {
    namespace bd =  boost::dispatch;
    namespace bs =  boost::simd;

    template < class A0 >
    struct logarithm< A0, tag::simd_type, double>
    {
      static BOOST_FORCEINLINE void kernel_log(const A0& a0,
                                    A0& dk,
                                    A0& hfsq,
                                    A0& s,
                                    A0& r,
                                    A0& f) BOOST_NOEXCEPT
    {
      using i_t = bd::as_integer_t<A0, signed>;
      i_t k;
      A0 x = a0;
      std::tie(x, k) = fast_(frexp)(x);
      const i_t x_lt_sqrthf = if_else_zero(is_greater(Sqrt_2o_2<A0>(), x),Mone<i_t>());
      k = k+x_lt_sqrthf; //+=
      f = dec(x+bitwise_and(x, x_lt_sqrthf));
      dk = tofloat(k);
      s = f/(Two<A0>()+f);
      A0 z = sqr(s);
      A0 w = sqr(z);
      A0 t1= w*horn<A0,
                    0x3fd999999997fa04ll,
                    0x3fcc71c51d8e78afll,
                    0x3fc39a09d078c69fll
                    > (w);
      A0 t2= z*horn<A0,
                    0x3fe5555555555593ll,
                    0x3fd2492494229359ll,
                    0x3fc7466496cb03dell,
                    0x3fc2f112df3e5244ll
                    > (w);
      r = t2+t1;
      hfsq = (Half<A0>()* sqr(f));
    }

    static BOOST_FORCEINLINE A0 log(const A0& a0) BOOST_NOEXCEPT
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y =  (dk* Log_2hi<A0>())-
        ((hfsq-(s*(hfsq+R)+(dk*Log_2lo<A0>())))-f);
      return finalize(a0, y);
    }

    static BOOST_FORCEINLINE A0 log2(const A0& a0) BOOST_NOEXCEPT
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y = -(hfsq-(s*(hfsq+R))-f)*Invlog_2<A0>()+dk;
      return finalize(a0, y);
    }

    static BOOST_FORCEINLINE A0 log10(const A0& a0) BOOST_NOEXCEPT
    {
      A0 dk, hfsq, s, R, f;
      kernel_log(a0, dk, hfsq, s, R, f);
      A0 y = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+dk*Log_2olog_10<A0>();
      return finalize(a0, y);
    }
  private:
    static BOOST_FORCEINLINE A0 finalize(const A0& a0, const A0& y) BOOST_NOEXCEPT
    {
    #ifdef BOOST_SIMD_NO_NANS
      auto test =  is_ltz(a0);
    #else
      auto test =  logical_or(is_ltz(a0), is_nan(a0));
    #endif
      A0 y1 = if_nan_else(test, y);
    #ifndef BOOST_SIMD_NO_INFINITIES
      y1 = if_else(is_equal(a0, Inf<A0>()), a0, y1);
    #endif
      return if_else(is_eqz(a0), Minf<A0>(), y1);
    }
  };
  }
} }

#endif
