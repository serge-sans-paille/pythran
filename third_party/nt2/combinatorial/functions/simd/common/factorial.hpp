//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_FACTORIAL_HPP_INCLUDED
#define NT2_COMBINATORIAL_FUNCTIONS_SIMD_COMMON_FACTORIAL_HPP_INCLUDED

#include <nt2/combinatorial/functions/factorial.hpp>
#include <nt2/include/constants/eight.hpp>
#include <nt2/include/constants/eleven.hpp>
#include <nt2/include/constants/fact_10.hpp>
#include <nt2/include/constants/fact_11.hpp>
#include <nt2/include/constants/fact_12.hpp>
#include <nt2/include/constants/fact_4.hpp>
#include <nt2/include/constants/fact_5.hpp>
#include <nt2/include/constants/fact_6.hpp>
#include <nt2/include/constants/fact_7.hpp>
#include <nt2/include/constants/fact_8.hpp>
#include <nt2/include/constants/fact_9.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/nine.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/seven.hpp>
#include <nt2/include/constants/six.hpp>
#include <nt2/include/constants/ten.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/twelve.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/abss.hpp>
#include <nt2/include/functions/simd/all.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/gamma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_greater_equal.hpp>
#include <nt2/include/functions/simd/is_less_equal.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/round2even.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/toint.hpp>
#include <nt2/include/functions/simd/trunc.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                       (A0)(X),
                      ((simd_<floating_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type              bA0;
      A0 r =  One<A0>();
      A0 a00 = nt2::trunc(nt2::abs(a0));
      r =  select(eq(a00, Two<A0>()),     Two<A0>(),    r);
      r =  select(eq(a00, Three<A0>()),   Six<A0>(),    r);
      r =  select(eq(a00, Four<A0>()),    Fact_4<A0>(), r);
      r =  select(eq(a00, Five<A0>()),    Fact_5<A0>(), r);
      r =  select(eq(a00, Six<A0>()),     Fact_6<A0>(), r);
      r =  select(eq(a00, Seven<A0>()),   Fact_7<A0>(), r);
      r =  select(eq(a00, Eight<A0>()),   Fact_8<A0>(), r);
      r =  select(eq(a00, Nine<A0>()),    Fact_9<A0>(), r);
      r =  select(eq(a00, Ten<A0>()),     Fact_10<A0>(),r);
      r =  select(eq(a00, Eleven<A0>()),  Fact_11<A0>(),r);
      r =  select(eq(a00, Twelve<A0>()),  Fact_12<A0>(),r);
      bA0 test = le(a00, Twelve<A0>());
      if (nt2::all(test))
        return r;
      else
        return select(test, r,
          nt2::round2even(nt2::gamma(oneplus(a00))));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<integer_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
      using boost::simd::bitwise_cast;
      typedef typename meta::as_floating<A0>::type ftype;
      ftype r = nt2::factorial(nt2::tofloat(a0));
      return select(gt(r,tofloat(Valmax<A0>())), Valmax<A0>(), bitwise_cast<A0>(nt2::toint(r)));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<int32_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  select(eq(a00, Two<A0>()),     Two<A0>(),  r);
      r =  select(eq(a00, Three<A0>()),   Six<A0>(), r);
      r =  select(eq(a00, Four<A0>()),    Fact_4<A0>(), r);
      r =  select(eq(a00, Five<A0>()),    Fact_5<A0>(), r);
      r =  select(eq(a00, Six<A0>()),     Fact_6<A0>() , r);
      r =  select(eq(a00, Seven<A0>()),   Fact_7<A0>(), r);
      r =  select(eq(a00, Eight<A0>()),   Fact_8<A0>() , r);
      r =  select(eq(a00, Nine<A0>()),    Fact_9<A0>(), r);
      r =  select(eq(a00, Ten<A0>()),     Fact_10<A0>(), r);
      r =  select(eq(a00, Eleven<A0>()),  Fact_11<A0>(), r);
      r =  select(eq(a00, Twelve<A0>()),  Fact_12<A0>(), r);
      return select(gt(a00, Twelve<A0>()), Valmax<A0>(), r);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<int16_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  select(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  select(eq(a00, Three<A0>()), Six<A0>(), r);
      r =  select(eq(a00, Four<A0>()), Fact_4<A0>(), r);
      r =  select(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      r =  select(eq(a00, Six<A0>()),  Fact_6<A0>() , r);
      r =  select(eq(a00, Seven<A0>()),Fact_7<A0>(), r);
      return select(ge(a00, Eight<A0>()), Valmax<A0>(), r);
    }
  };
  NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<uint16_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  select(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  select(eq(a00, Three<A0>()), Six<A0>(), r);
      r =  select(eq(a00, Four<A0>()), Fact_4<A0>(), r);
      r =  select(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      r =  select(eq(a00, Six<A0>()),  Fact_6<A0>() , r);
      r =  select(eq(a00, Seven<A0>()), Fact_7<A0>(), r);
      r =  select(eq(a00, Eight<A0>()), Fact_8<A0>() , r);
      return select(ge(a00, Nine<A0>()), Valmax<A0>(), r);
    }
  };

    NT2_FUNCTOR_IMPLEMENTATION(nt2::tag::factorial_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type8_<A0>,X>))
                     )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      const A0 a00 = abss(a0);
      A0 r =  One<A0>();
      r =  select(eq(a00, Two<A0>()), Two<A0>(),  r);
      r =  select(eq(a00, Three<A0>()), Six<A0>(), r);
      r =  select(eq(a00, Four<A0>()), Fact_4<A0>(), r);
      r =  select(eq(a00, Five<A0>()), Fact_5<A0>(), r);
      return select(gt(a00, Five<A0>()), Valmax<A0>(), r);
    }
  };
} }
#endif
