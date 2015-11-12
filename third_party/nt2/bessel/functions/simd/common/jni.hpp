//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SIMD_COMMON_JNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SIMD_COMMON_JNI_HPP_INCLUDED
#include <nt2/bessel/functions/jni.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/simd/meta/is_real_convertible.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/sqrt.hpp>
#include <nt2/include/functions/simd/cos.hpp>
#include <nt2/include/functions/simd/j0.hpp>
#include <nt2/include/functions/simd/j1.hpp>
#include <nt2/include/functions/simd/cospi.hpp>
#include <nt2/include/functions/simd/splat.hpp>
#include <nt2/include/functions/simd/is_less.hpp>
#include <nt2/include/functions/simd/is_greater.hpp>
#include <nt2/include/functions/simd/if_else.hpp>




/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<arithmetic_<A1>,X>))
                            )
  {

    typedef typename meta::as_floating<A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::jni(a0, tofloat(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)(X)
                            , (scalar_< integer_<A0> >)((simd_<floating_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef A1 type;
      type x = a1;
      const int32_t n1 = nt2::abs(a0);
      type sign = splat<type>(a0<0?nt2::cospi(n1):1);
      if( n1 == 0 )
        return( sign * j0(x) );
      if( n1 == 1 )
        return( sign * j1(x) );
      if( n1 == 2 )
        return mul(sign, (mul(Two<type>(), j1(x) / x)  -  j0(x)) );

      /* continued fraction */
      int k = 24;
      type pk = splat<type>(2*(n1 + k));
      type ans = pk;
      type xk = sqr(x);
      do {
        pk  = pk - Two<type>();
        ans = pk - (xk/ans);
      }
      while( --k > 0 );
      /* backward recurrence */

      pk = One<type>();
      /*pkm1 = 1.0/ans;*/
      type xinv = rec(x);
      type pkm1 = ans * xinv;
      k = n1-1;
      type r = splat<type>(2.0f*k);

      do{
        const type pkm2 = (pkm1 * r  -  pk * x) * xinv;
        pk = pkm1;
        pkm1 = pkm2;
        r = r-Two<type>();
      }
      while( --k > 0 );
      return sign*sel(is_greater(nt2::abs(pk), nt2::abs(pkm1)),j1(x)/pk, j0(x)/pkm1);
    }
  };
} }


#endif
