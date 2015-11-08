//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLIPKE_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLIPKE_HPP_INCLUDED
#include <nt2/elliptic/functions/ellipke.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/ldexp.hpp>
#include <nt2/include/functions/simd/logical_or.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION(  nt2::tag::ellipke_, tag::cpu_,
                               (A0)(A1)(X),
                               ((simd_<floating_<A0>,X >))
                               ((scalar_<floating_<A1> >))
                               ((simd_<floating_<A0>,X >))
                               ((simd_<floating_<A0>,X >))
                            )
  {
    typedef void result_type;
    inline result_type operator()(A0 const& a0,
                                  A1 const& a1, A0 & a2,A0 & a3) const
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::as_integer<A0>::type iA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      bA0 isnan =  nt2::logical_or(nt2::is_ltz(a0), nt2::gt(a0, nt2::One<A0>()));
      A0 m = nt2::if_zero_else(isnan, a0);
      A0 aa0 = nt2::One<A0>();
      A0 bb0 = nt2::sqrt(nt2::oneminus(m));
      A0 s0 = m;
      int32_t i1 = 0;
      sA0 mm = nt2::One<sA0>();
      A0 aa1 = nt2::Zero<A0>();
      while (nt2::gt(mm, a1))
      {
        aa1 = nt2::average(aa0, bb0);
        A0 bb1 = nt2::sqrt(aa0*bb0);
        A0 cc1 = nt2::average(aa0, -bb0);
        ++i1;
        A0 w1 = nt2::ldexp(nt2::sqr(cc1), nt2::splat<iA0>(i1));
        mm =  nt2::maximum(w1);
        s0 += w1;
        aa0 = aa1;
        bb0 = bb1;
      };
      bA0 iseqm1 = eq(m, One<A0>());
      a2 = nt2::if_nan_else(isnan, nt2::if_else(iseqm1,nt2::Inf<A0>(), nt2::Pio_2<A0>()/aa1));
      a3 = nt2::if_nan_else(isnan, nt2::if_else(iseqm1,nt2::One<A0>(), a2*(nt2::One<A0>()-s0*nt2::Half<A0>())));
    }
  };

} }
#endif
