//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SIMD_COMMON_J0_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SIMD_COMMON_J0_HPP_INCLUDED
#include <nt2/bessel/functions/j0.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/if_zero_else.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/cos.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/max.hpp>
#include <nt2/include/functions/simd/min.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::j0_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(1)
    {
      return nt2::j0(tofloat(a0));
    }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is double
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::j0_, tag::cpu_
                     , (A0)(X)
                     , ((simd_<double_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
     return map(functor<tag::j0_>(), a0);
      }
  };

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is float
  /////////////////////////////////////////////////////////////////////////////
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::j0_, tag::cpu_,
                    (A0)(X),
                    ((simd_<single_<A0>,X>))
                    )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        typedef typename meta::as_logical<A0>::type bA0;
        A0 x   =  nt2::abs(a0);
        bA0 lt2 = lt(x, Two<A0>());
        if (nt2::all(lt2))
          return branch1(x);
        else
          return if_else (lt2, branch1(x), branch2(x));
       // as branch1 is quick there is no need for an "else if" case
       // computing only branch2,  this probably due to the double pipeline
      }
  private :
    template < class AA0 > static inline AA0 branch1(const AA0& x)
      {
       typedef typename meta::scalar_of<AA0>::type stype;
       const AA0 z = sqr(x);
       return (z-single_constant<AA0,0x40b90fdc> ())*
         horner< NT2_HORNER_COEFF_T(stype, 5,
                                 (0xb382511c,
                                  0x36d660a0,
                                  0xb9d01fb1,
                                  0x3c5a6271,
                                  0xbe3110a6
                                  ) ) > (z);
  }
  template < class AA0 > static inline AA0 branch2(const AA0& x)
  {
    typedef typename meta::scalar_of<AA0>::type stype;
    AA0 q = rec(x);
    AA0 w = sqrt(q);
    AA0 p3 = w *
      horner< NT2_HORNER_COEFF_T(stype, 8,
                             (0xbd8c100e,
                              0x3e3ef887,
                              0xbe5ba616,
                              0x3df54214,
                              0xbb69539e,
                              0xbd4b8bc1,
                              0xb6612dc2,
                              0x3f4c422a
                              ) ) > (q);
    w = sqr(q);
    AA0 xn =  q*
      horner< NT2_HORNER_COEFF_T(stype, 8,
                             (0x4201aee0,
                              0xc2113945,
                              0x418c7f6a,
                              0xc09f3306,
                              0x3f8040aa,
                              0xbe46a57f,
                              0x3d84ed6e,
                              0xbdffff97
                              ) ) > (w)-Pio_4<AA0>();
      return if_zero_else(eq(x, Inf<AA0>()), p3*cos(xn+x));
    }
  };
} }

#endif
