//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFINV_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_ERFINV_HPP_INCLUDED

#include <nt2/euler/functions/erfinv.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/real_splat.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/signnz.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 w = -log(oneminus(a0)*oneplus(a0));
      bA0 test = lt(w, Five<A0>());
      const A0 Two5 =  single_constant<A0, 0x40200000>();  //2.5
      w = if_else(test, w-Two5, sqrt(w)-Three<A0>());
      std::size_t nb = inbtrue(test);
      A0 r1;
      if(nb > 0)
      {
        r1 = a0*details::erfinv_kernel<A0>::erfinv1(w);
        if(nb >= meta::cardinal_of<A0>::value) return r1;
      }
      A0 r2 = a0*details::erfinv_kernel<A0>::erfinv2(w);
      return if_else( eq(w, Inf<A0>())
                    , signnz(a0)*w
                    , if_else(test, r1, r2)
                    );
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::erfinv_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef typename meta::as_floating<A0>::type result_type;
    typedef typename meta::scalar_of<A0>::type sA0;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 w = -log(oneminus(a0)*oneplus(a0));
      const A0 Six25    =  double_constant<A0, 0x4019000000000000ll>(); //6.25
      const A0 Three125 =  double_constant<A0, 0x4009000000000000ll>(); //3.125
      const A0 Three25  =  double_constant<A0, 0x400a000000000000ll>(); //3.25
      const A0 Sixteen  =  double_constant<A0, 0x4030000000000000ll>(); //16.0
      bA0 test1 = lt(w, Six25);
      bA0 test2 = lt(w, Sixteen);
      w =  if_else(test1, w, sqrt(w));
      w -= if_else(test1, Three125,
                   if_else(test2, Three25,
                           Five<A0>()
                          )
                  );
      std::size_t nb = inbtrue(test1);
      A0 r1;
      if(nb > 0)
      {
        r1 = a0*details::erfinv_kernel<A0>::erfinv1(w);
        if(nb >= meta::cardinal_of<A0>::value) return r1;
      }
      bA0 test3 = nt2::logical_andnot(test2, test1);
      std::size_t nb1 = inbtrue(test3);
      if(nb1 > 0)
      {
        A0 r2 = a0*details::erfinv_kernel<A0>::erfinv2(w);
        r1 = nt2::if_else(test1, r1, r2);
        nb += nb1;
        if(nb >= meta::cardinal_of<A0>::value) return r1;
      }
      r1 = if_else(test2, r1, a0*details::erfinv_kernel<A0>::erfinv3(w));
      return if_else(eq(w, Inf<A0>()), signnz(a0)*w, r1);
    }
  };
} }
#endif
