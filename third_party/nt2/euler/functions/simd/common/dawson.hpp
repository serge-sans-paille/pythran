//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EULER_FUNCTIONS_SIMD_COMMON_DAWSON_HPP_INCLUDED
#define NT2_EULER_FUNCTIONS_SIMD_COMMON_DAWSON_HPP_INCLUDED
#include <nt2/euler/functions/dawson.hpp>
#include <nt2/euler/functions/details/dawson_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/copysign.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/logical_andnot.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::dawson_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 x =  nt2::abs(a0);
      A0 xx = nt2::sqr(x);
      A0 lim1 = nt2::splat<A0>(3.25);
      A0 lim2 = nt2::splat<A0>(6.25);
      bA0 test1 = lt(x, lim1);
      A0 r1 = nt2::Zero<A0>();
      std::size_t nb = inbtrue(test1);
      if( nb > 0 )
      {
        r1 = x * details::dawson_kernel<A0>::dawson1(xx);
        if(nb >= meta::cardinal_of<A0>::value)
          return  nt2::copysign(r1, a0);

      }
      bA0 test2 = nt2::lt(x, lim2);
      bA0 test3 = nt2::logical_andnot(test2, test1);
      std::size_t nb1 = nt2::inbtrue(test3);
      xx =  rec(xx);
      if(nb1 > 0)
      {
        A0 y =   nt2::Half<A0>()*details::dawson_kernel<A0>::dawson2(xx, x);
        r1 = if_else(test3, y, r1);
        if(nb1 >= meta::cardinal_of<A0>::value)
          return  nt2::copysign(r1, a0);
      }

       /* 6.25 to 1.0e9 */
      r1 =  if_else(test2, r1, nt2::Half<A0>()*details::dawson_kernel<A0>::dawson3(xx, x));
      return  nt2::copysign(r1, a0);
    }
  };

} }

#endif
