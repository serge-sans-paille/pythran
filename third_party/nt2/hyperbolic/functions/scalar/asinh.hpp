//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ASINH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SCALAR_ASINH_HPP_INCLUDED
#include <nt2/hyperbolic/functions/asinh.hpp>
#include <nt2/include/constants/log_2.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/oneosqrteps.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/bitofsign.hpp>
#include <nt2/include/functions/scalar/bitwise_xor.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/hypot.hpp>
#include <nt2/include/functions/scalar/log.hpp>
#include <nt2/include/functions/scalar/log1p.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/polynomials/functions/scalar/impl/horner.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      A0 x = nt2::abs(a0);
      if  (BOOST_UNLIKELY(x < nt2::Sqrteps<A0>() ))
      {
        return a0;
      }
      else
      {
        A0 z;
        if (x < 0.5)
        {
          A0 invx = nt2::rec(x);
          z = nt2::log1p(x + x/(invx + nt2::sqrt(fma(invx, invx, nt2::One<A0>()))));
        }
        else if (BOOST_UNLIKELY(x > Oneosqrteps<A0>()))
        {
          z = log(x)+Log_2<A0>();
        }
        else
        {
          z =  log(x+hypot(One<A0>(), x));
        }
        return b_xor(z, bitofsign(a0));
      }
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::asinh_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL(1)
    {
      // Exhaustive test for: boost::dispatch::functor<nt2::tag::asinh_, boost::simd::tag::sse4_2_>
      //              versus:  float(boost::math::asinh(double)
      //              With T: float
      //            in range: [-3.40282e+38, 3.40282e+38]
      // 4278190078 values computed.
      // 3628470338 values (84.81%)  within 0.0 ULPs
      //  649693884 values (15.19%)  within 0.5 ULPs
      //      25856 values ( 0.00%)  within 1.0 ULPs
      A0 x = nt2::abs(a0);
      A0 x2 = nt2::sqr(x);
      A0 z = Zero<A0>();

      if( x < 0.5f)
      {
        z = horner < NT2_HORNER_COEFF_T(A0, 5,
                                        ( 0x3ca4d6e6
                                        , 0xbd2ee581
                                        , 0x3d9949b1
                                        , 0xbe2aa9ad
                                        , 0x3f800000
                                        )
                                       )> (x2)*x;
      }
      else if (BOOST_UNLIKELY(x > Oneosqrteps<A0>()))
      {
        z = log(x)+Log_2<A0>();
      }
      else
      {
        z =  log(x+hypot(One<A0>(), x));
      }
      return b_xor(z, bitofsign(a0));
    }
  };
} }
#endif
