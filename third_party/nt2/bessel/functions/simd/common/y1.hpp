//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SIMD_COMMON_Y1_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SIMD_COMMON_Y1_HPP_INCLUDED
#include <nt2/bessel/functions/y1.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/j1.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/any.hpp>
#include <nt2/include/functions/simd/is_eqz.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return nt2::y1(tofloat(a0));
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                        , (A0)(X)
                     , ((simd_<double_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
     return map(functor<tag::y1_>(), a0);
      }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::y1_, tag::cpu_
                     , (A0)(X)
                     , ((simd_<single_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      bA0 a0lt2 = lt(a0, Two<A0>());
      A0 q = rec(a0);
      A0 p2 = Zero<A0>();
      if (nt2::any(a0lt2))
      {
        A0 z = sqr(a0);
        p2 = (z-single_constant<A0, 0x40954ae7> ())*a0*
          horner< NT2_HORNER_COEFF_T(sA0, 5,
                                     (0x320a80f5,
                                      0xb57eeb2e,
                                      0x388ceb47,
                                      0xbb2d21cf,
                                      0x3d2c210b
                                       ) ) > (z);
        p2 = p2+single_constant<A0, 0x3f22f983>()*(j1(a0)*log(a0)-q);
        p2 = sel(is_eqz(a0), Minf<A0>(), p2);
        if (nt2::all(a0lt2)) return p2;
     }
      A0 w = sqrt(q);
      A0 p3 = w *
        horner< NT2_HORNER_COEFF_T(sA0, 8,
                                   (0x3d8d98f9,
                                    0xbe69f6b3,
                                    0x3ea0ad85,
                                    0xbe574699,
                                    0x3bb21b25,
                                    0x3e18ec50,
                                    0x36a6f7c5,
                                    0x3f4c4229
                                     ) ) > (q);
      w = sqr(q);
      A0 xn =  q*
        horner< NT2_HORNER_COEFF_T(sA0, 8,
                                   (0xc233e16d,
                                    0x424af04a,
                                    0xc1c6dca7,
                                    0x40e72299,
                                    0xbfc5bd69,
                                    0x3eb364d9,
                                    0xbe27bad7,
                                    0x3ebfffdd
                                     ) ) > (w)-single_constant<A0,0x4016cbe4 > ();
      p3 = p3*sin(xn+a0);
      return if_zero_else(is_inf(a0), select(a0lt2, p2, p3));
    }
  };
} }


#endif
