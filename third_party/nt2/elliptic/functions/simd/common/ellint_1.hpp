//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLINT_1_HPP_INCLUDED
#define NT2_ELLIPTIC_FUNCTIONS_SIMD_COMMON_ELLINT_1_HPP_INCLUDED

#include <nt2/elliptic/functions/ellint_1.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/pio_2.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/average.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/include/functions/simd/if_else.hpp>
#include <nt2/include/functions/simd/is_equal.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/maximum.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ellint_1_, tag::cpu_
                            , (A0)(X)
                            , ((simd_< floating_<A0>,X >))
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<result_type>::type scalar_type;
      result_type a = One<result_type>();
      result_type b = nt2::sqrt(oneminus(sqr(a0)));
      result_type c = a0;
      while (nt2::maximum(abs(c)) > Eps<scalar_type>())
      {
        result_type an=average(a, b);
        result_type bn=nt2::sqrt(a*b);
        c=average(a, -b);
        a=an;
        b=bn;
      }
      return if_nan_else(gt(nt2::abs(a0), One<result_type>()),
                         if_else(eq(a0, One<result_type>()), Inf<result_type>(), Pio_2<result_type>()/a)
                        );
    }
  };
} }

#endif
