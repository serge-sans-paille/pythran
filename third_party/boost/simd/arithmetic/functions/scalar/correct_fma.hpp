//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_CORRECT_FMA_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_CORRECT_FMA_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/correct_fma.hpp>
#include <boost/simd/include/functions/scalar/two_add.hpp>
#include <boost/simd/include/functions/scalar/two_prod.hpp>
#include <boost/simd/include/functions/scalar/ldexp.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/include/functions/scalar/exponent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::correct_fma_, tag::cpu_
                                   , (A0)
                                   , (scalar_< single_<A0> >)
                                     (scalar_< single_<A0> >)
                                     (scalar_< single_<A0> >)
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      return static_cast<A0>( static_cast<double>(a0)*static_cast<double>(a1)
                            + static_cast<double>(a2)
                            );
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::correct_fma_, tag::cpu_
                                   , (A0)
                                   , (scalar_< floating_<A0> >)
                                     (scalar_< floating_<A0> >)
                                     (scalar_< floating_<A0> >)
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
      result_type p, rp, s, rs;
#ifndef BOOST_SIMD_DONT_CARE_FMA_OVERFLOW
      typedef typename boost::dispatch::meta::as_integer<A0>::type iA0;
      iA0 e0 = exponent(a0);
      iA0 e1 = exponent(a1);
      iA0 e = -boost::simd::max(e0, e1)/2;
      result_type ae2  = ldexp(a2, e);
      bool choose = (e0 > e1);
      result_type amax = choose ? ldexp(a0, e) : ldexp(a1, e);
      result_type amin = choose ? a1 : a0;
      two_prod(amax, amin, p, rp);
      two_add(p, ae2, s, rs);
      return ldexp(s+(rp+rs), -e);
#else
      two_prod(a0, a1, p, rp);
      two_add(p, a2, s, rs);
      return s+(rp+rs);
#endif
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::correct_fma_, tag::cpu_
                                   , (A0)
                                   , (scalar_< integer_<A0> >)
                                     (scalar_< integer_<A0> >)
                                     (scalar_< integer_<A0> >)
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(3)
    {
     return a0*a1+a2;
    }
  };


} } }


#endif
