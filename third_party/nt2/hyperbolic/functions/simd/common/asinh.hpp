//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ASINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SIMD_COMMON_ASINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/asinh.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/oneosqrteps.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/bitofsign.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/bitwise_xor.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/hypot.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/inbtrue.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/minusone.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneplus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/config.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#endif

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<double_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_logical<A0>::type bA0;
      A0 x =  nt2::abs(a0);
      bA0 test = gt(x,Oneosqrteps<A0>());
      A0 z = if_else(test,minusone(x), x+sqr(x)/nt2::oneplus(hypot(One<A0>(), x)));
      #ifndef BOOST_SIMD_NO_INFINITIES
      z = if_else(is_equal(x, Inf<A0>()),x, z);
      #endif
      z =  seladd(test, log1p(z), Log_2<A0>());
      return bitwise_xor(bitofsign(a0), z);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<single_<A0>,X>))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      // Exhaustive test for: boost::dispatch::functor<nt2::tag::asinh_, boost::simd::tag::sse4_2_>
      //              versus: float(boost::math::asinh(double)
      //              With T: boost::simd::native<float, boost::simd::tag::sse_, void>
      //            in range: [-3.40282e+38, 3.40282e+38]
      // 4278190076 values computed.
      // 3619320676 values (84.60%)  within 0.0 ULPs
      //  658843138 values (15.40%)  within 0.5 ULPs
      //      26262 values ( 0.00%)  within 1.0 ULPs
      typedef typename meta::as_logical<A0>::type bA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 x = nt2::abs(a0);
      bA0 lthalf = lt(x,Half<A0>());
      A0 x2 = nt2::sqr(x);
      A0 z = Zero<A0>();
      std::size_t nb = inbtrue(lthalf);
      A0 bts = bitofsign(a0);
      if(nb > 0)
      {
        z = horner < NT2_HORNER_COEFF_T(sA0, 5,
                                        ( 0x3ca4d6e6
                                        , 0xbd2ee581
                                        , 0x3d9949b1
                                        , 0xbe2aa9ad
                                        , 0x3f800000
                                        )
                                       )> (x2)*x;
        if(nb >= meta::cardinal_of<A0>::value) return  b_xor(z, bts);
      }
      A0 tmp =  if_else(gt(x, Oneosqrteps<A0>()),
                       x, average(x, hypot(One<A0>(), x)));
     return b_xor(if_else(lthalf, z, log(tmp)+Log_2<A0>()), bts);
    }
  };
} }
#endif
