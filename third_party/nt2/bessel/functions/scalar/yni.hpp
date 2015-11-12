//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_BESSEL_FUNCTIONS_SCALAR_YNI_HPP_INCLUDED
#define NT2_BESSEL_FUNCTIONS_SCALAR_YNI_HPP_INCLUDED

#include <nt2/bessel/functions/yni.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/sqrt.hpp>
#include <nt2/include/functions/scalar/cos.hpp>
#include <nt2/include/functions/scalar/cospi.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/y0.hpp>
#include <nt2/include/functions/scalar/y1.hpp>
#include <nt2/include/constants/digits.hpp>
#include <nt2/include/constants/real.hpp>
#include <boost/simd/sdk/math.hpp>
#include <boost/simd/sdk/config.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< arithmetic_<A1> >)
                            )
  {
    typedef typename boost::dispatch::meta::as_floating<A0,A1>::type result_type;
    NT2_FUNCTOR_CALL(2)
    {
      return nt2::yni(a0, result_type(a1));
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is double
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< double_<A1> >)
                            )
  {
    typedef A1 result_type;
    NT2_FUNCTOR_CALL(2)
    {
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a1)) return Nan<result_type>();
      if (is_inf(a1)) return Zero<result_type>();
#endif
      if (is_eqz(a1)) return Minf<result_type>();
    #ifdef BOOST_SIMD_HAS__YN
      return ::_yn(a0, a1);
    #elif defined(BOOST_SIMD_HAS_YN)
      return ::yn(a0, a1);
    #else
      #error yn not supported
    #endif
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A1 is float
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::yni_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< integer_<A0> >)(scalar_< single_<A1> >)
                            )
  {

    typedef A1 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if (is_ltz(a1)) return Nan<result_type>();
#ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a1)) return Nan<result_type>();
      if (is_inf(a1)) return Zero<result_type>();
#endif
      if (is_eqz(a1)) return Minf<result_type>();
      result_type x = a1;
      const size_t n1 = nt2::abs(a0);
      result_type sign = (a0<0)?nt2::cospi(n1):1;
      if( n1 == 0u ) return( sign * nt2::y0(x) );
      if( n1 == 1u ) return( sign * nt2::y1(x) );
      //      result_type an1 = n1;
      /* forward recurrence on n */

      result_type anm2 = nt2::y0(x);
      result_type anm1 = nt2::y1(x);
      size_t k = 1;
      result_type r = result_type(k << 1);
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
      return sign*an;
      //     return ::ynf(a0, a1);
    }
  };
} }


#endif
