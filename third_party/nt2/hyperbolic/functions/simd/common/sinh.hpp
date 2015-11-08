//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_SINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/sinh.hpp>
#include <nt2/hyperbolic/functions/details/sinh_kernel.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/maxlog.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))
                            )
  {

    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      result_type x = nt2::abs(a0);
      bA0 lt1= lt(x, One<A0>());
      A0 bts = bitofsign(a0);
      std::size_t nb = inbtrue(lt1);
      A0 z = Zero<A0>();
      if(nb > 0)
      {
        A0 x2 = sqr(x);
        z = details::sinh_kernel<A0>::compute(x, x2);
        if(nb >= meta::cardinal_of<A0>::value) return  b_xor(z, bts);
      }
      bA0 test1 = gt(x, Maxlog<A0>()-Log_2<A0>());
      A0 fac = if_else(test1, Half<A0>(), One<A0>());
      A0 tmp = exp(x*fac);
      A0 tmp1 = Half<A0>()*tmp;
      A0 r =  if_else(test1, tmp1*tmp, tmp1-Half<A0>()*rec(tmp));
      return b_xor(if_else(lt1, z, r), bts);
    }
  };
} }
#endif
