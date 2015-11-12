//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOMIALS_FUNCTIONS_SIMD_COMMON_TCHEBEVAL_HPP_INCLUDED
#define NT2_POLYNOMIALS_FUNCTIONS_SIMD_COMMON_TCHEBEVAL_HPP_INCLUDED

#include <nt2/polynomials/functions/tchebeval.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/fma.hpp>
#include <nt2/include/functions/simd/tofloat.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/functions/simd/plus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tchebeval_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))(fusion_sequence_<A1>)
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::tchebeval(tofloat(a0), a1);
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is floating_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::tchebeval_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<floating_<A0>,X>))(fusion_sequence_<A1>)
                            )
  {

    typedef typename meta::as_floating<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {

      typename A1::const_iterator p = a1.begin();
      A0 b0 = splat<A0>(*p++);
      A0 b1 = Zero<A0>();
      A0 b2 = Zero<A0>();
      while (p != a1.end())
      {
        b2 = -b1;
        b1 = b0;
        b0 = fma(a0, b1, b2)  + splat<A0>(*p++);
      }
      return average(b0, b2);

    }
  };
} }

#endif
