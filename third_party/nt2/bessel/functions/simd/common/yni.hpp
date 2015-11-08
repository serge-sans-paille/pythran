//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SIMD_COMMON_YNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SIMD_COMMON_YNI_HPP_INCLUDED

#include <nt2/bessel/functions/yni.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/minus.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/cos.hpp>
#include <nt2/include/functions/simd/y0.hpp>
#include <nt2/include/functions/simd/y1.hpp>
#include <nt2/include/functions/simd/cospi.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/if_allbits_else.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<arithmetic_<A1>,X> ))
                            )
  {
    typedef typename meta::as_floating<A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::yni(a0, tofloat(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)
                              ((simd_<floating_<A1>,X>))
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      result_type x = a1;
      const int32_t n1 = nt2::abs(a0);
      result_type sign = splat<result_type>((a0<0)?cospi(n1):1);
      if( n1 == 0 ) return( sign * y0(x) );
      if( n1 == 1 ) return( sign * y1(x) );
      /* forward recurrence on n */

      result_type anm2 = y0(x);
      result_type anm1 = y1(x);
      int32_t k = 1;
      result_type r = splat<result_type>(k << 1);
      result_type xinv = rec(x);
      result_type an;
      do
        {
          an = r*anm1*xinv-anm2;
          anm2 = anm1;
          anm1 = an;
          r +=Two<result_type>();
          ++k;
        }
      while( k < n1 );
      return if_nan_else(is_ltz(a1),sign*an);
    }
  };
} }

#endif
