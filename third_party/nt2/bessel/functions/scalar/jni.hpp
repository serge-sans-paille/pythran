//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_JNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_JNI_HPP_INCLUDED
#include <nt2/bessel/functions/jni.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/functions/scalar/j0.hpp>
#include <nt2/include/functions/scalar/j1.hpp>
#include <nt2/include/functions/scalar/cospi.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/include/functions/scalar/is_less.hpp>
#include <nt2/include/functions/scalar/is_greater.hpp>
#include <nt2/include/functions/scalar/splat.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/simd/sdk/config.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {

    typedef typename boost::dispatch::meta::as_floating<A0,A1>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      return nt2::jni(a0, result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< double_<A1> >)
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
#ifndef BOOST_SIMD_NO_INVALIDS
      if(nt2::is_inf(a1)) return Zero<A0>();
#endif
    #if defined(BOOST_SIMD_HAS__JN)
      return ::_jn(a0, a1);
    #elif defined(BOOST_SIMD_HAS_JN)
      return ::jn(a0, a1);
    #else
      #error jn not supported
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::jni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< single_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      result_type x = a1;
      const size_t n1 = nt2::abs(a0);
      result_type sign = a0<Zero<A0>()?cospi(n1):One<A0>();
      if( n1 == 0 )
        return( sign * nt2::j0(x) );
      if( n1 == 1 )
        return( sign * nt2::j1(x) );
      if( n1 == 2 )
        return mul(sign, (mul(Two<result_type>(), nt2::j1(x) / x)  -  nt2::j0(x)) );

      /* continued fraction */
      ptrdiff_t k = 24;
      result_type pk = Two<result_type>()*(result_type(n1) + result_type(k));
      result_type ans = pk;
      result_type xk = sqr(x);
      do {
        pk  = pk - Two<result_type>();
        ans = pk - (xk/ans);
      }
      while( --k > 0 );
      /* backward recurrence */

      pk = One<result_type>();
      /*pkm1 = 1.0/ans;*/
      result_type xinv = rec(x);
      result_type pkm1 = ans * xinv;
      k = n1-1;
      result_type r = 2.0f*k;

      do{
        const result_type pkm2 = (pkm1 * r  -  pk * x) * xinv;
        pk = pkm1;
        pkm1 = pkm2;
        r -= Two<result_type>();
      }
      while( --k > 0 );
      return sign*select(gt(abs(pk), nt2::abs(pkm1)),nt2::j1(x)/pk, nt2::j0(x)/pkm1);
      //     return ::jnf(a0, a1);
    }
  };
} }


#endif
