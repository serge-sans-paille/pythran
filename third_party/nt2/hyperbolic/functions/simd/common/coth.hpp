//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_COTH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_COTH_HPP_INCLUDED

#include <nt2/hyperbolic/functions/coth.hpp>
#include <nt2/hyperbolic/functions/details/tanh_kernel.hpp>
#include <nt2/include/constants/fiveo_8.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/coth.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::coth_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>, X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) is less than 5/8 sinh is computed using a polynomial(float)
      // (respectively rational(double)) approx inspirated from cephes.
      // else
      // coth(a0) is  sign(a0)*(1 + 2/(exp(2*x)-1))
      //////////////////////////////////////////////////////////////////////////////
      typedef typename meta::as_logical<A0>::type bA0;
      result_type x = nt2::abs(a0);
      bA0 test0= lt(x, Fiveo_8<A0>());
      A0 bts = bitofsign(a0);
      std::size_t nb = inbtrue(test0);
      A0 z = One<A0>();
      if(nb> 0)
      {
        z = details::tanh_kernel<A0>::coth(x, sqr(x));
        if(nb >= meta::cardinal_of<A0>::value) return  b_xor(z, bts);
      }
      A0 r = fma(Two<A0>(), rec(minusone(exp(x+x))), One<A0>());
      return b_xor(if_else(test0, z, r), bts);
    }
  };
} }
#endif
