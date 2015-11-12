//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_D_EXPO_REDUCTION_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_IMPL_EXPO_D_EXPO_REDUCTION_HPP_INCLUDED

#include <nt2/exponential/functions/scalar/impl/selection_tags.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/constants/minlog.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/constants/invlog_2.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/fnms.hpp>
#include <nt2/include/constants/log_2hi.hpp>
#include <nt2/include/constants/log_2lo.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/constants/minlog2.hpp>
#include <nt2/include/constants/maxlog2.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/minlog10.hpp>
#include <nt2/include/constants/maxlog10.hpp>
#include <nt2/include/constants/invlog10_2.hpp>
#include <nt2/include/constants/log10_2hi.hpp>
#include <nt2/include/constants/log10_2lo.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>

namespace nt2 { namespace details
{
  template < class A0> struct exp_reduction < A0, natural_tag, double>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog<A0>());
    }

    static inline A0 reduce(const A0& a0, A0& hi, A0& lo, A0& x)
    {
      A0 k  = nt2::round2even(Invlog_2<A0>()*a0);
      hi = fnms(k, Log_2hi<A0>(), a0); //a0-k*L
      lo = k*Log_2lo<A0>();
      x  = hi-lo;
      return k;
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 const t = nt2::sqr(x);
      return fnms(t, nt2::horner<NT2_HORNER_COEFF_T(sA0, 5,
                                                    ( 0x3e66376972bea4d0ll, 0xbebbbd41c5d26bf1ll
                                                    , 0x3f11566aaf25de2cll, 0xbf66c16c16bebd93ll
                                                    , 0x3fc555555555553ell
                                                    )
                                                   )>(t), x); //x-h*t
    }

    static inline A0 finalize(const A0& x, const A0& c,
                              const A0& hi,const A0& lo)
    {
      return  nt2::oneminus(((lo-(x*c)/(nt2::Two<A0>()-c))-hi));
    }

  };

  template < class A0 > struct exp_reduction < A0, two_tag, double>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog2<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog2<A0>());
    }

    static inline A0 reduce(const A0& a0, const A0&, const A0&, A0& x)
    {
      A0 k = nt2::round2even(a0);
      x = (a0 - k)*nt2::Log_2<A0>();
      return k;
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      const A0 t =  nt2::sqr(x);
      return fnms(t, nt2::horner<NT2_HORNER_COEFF_T(sA0, 5,
                                                    ( 0x3e66376972bea4d0ll
                                                    , 0xbebbbd41c5d26bf1ll
                                                    , 0x3f11566aaf25de2cll
                                                    , 0xbf66c16c16bebd93ll
                                                    , 0x3fc555555555553ell
                                                    )
                                                   )> (t), x); //x-h*t
    }

    static inline A0 finalize(const A0& x, const A0& c,
                              const A0&,   const A0& )
    {
      return nt2::oneminus(((-(x*c)/(nt2::Two<A0>()-c))-x));
    }
  };

  template < class A0 > struct exp_reduction < A0, ten_tag, double>
  {
    typedef typename meta::as_logical<A0>::type bA0;
    static inline bA0 isgemaxlog(const A0 & a0)
    {
      return nt2::ge(a0,Maxlog10<A0>());
    }

    static inline bA0 isleminlog(const A0 & a0)
    {
      return nt2::le(a0,Minlog10<A0>());
    }

    static inline A0 reduce(const A0& a0, A0&, A0&, A0& x)
    {
      A0 k  = round2even(Invlog10_2<A0>()*a0);
      x = fnms(k, Log10_2hi<A0>(), a0);
      x = fnms(k, Log10_2lo<A0>(), x);
      return k;
    }

    static inline A0 approx(const A0& x)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 xx =  nt2::sqr(x);
      A0 px = x*nt2::horner<NT2_HORNER_COEFF_T(sA0, 4,
                                               (0x3fa4fd75f3062dd4ll,
                                                0x40277d9474c55934ll,
                                                0x40796b7a050349e4ll,
                                                0x40a2b4798e134a01ll)
                                              )> (xx);
      A0 x2 =  px/(nt2::horner<NT2_HORNER_COEFF_T(sA0, 4,
                                                  (0x3ff0000000000000ll,
                                                   0x405545fdce51ca08ll,
                                                   0x4093e05eefd67782ll,
                                                   0x40a03f37650df6e2ll)
                                                 )> (xx)-px);
      return nt2::oneplus(x2+x2);
    }

    static inline A0 finalize(const A0&,  const A0& c,
                              const A0&,  const A0& )
    {
      return c;
    }

  };
} }


#endif
