//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/hypot.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/include/functions/scalar/abs.hpp>
#include <boost/simd/include/functions/scalar/exponent.hpp>
#include <boost/simd/include/functions/scalar/ldexp.hpp>
#include <boost/simd/include/functions/scalar/sqr.hpp>
#include <boost/simd/include/functions/scalar/sqrt.hpp>
#include <boost/simd/include/functions/scalar/max.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/constants/maxexponentm1.hpp>
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/simd/include/constants/zero.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/include/functions/scalar/is_inf.hpp>
#include <boost/simd/include/functions/scalar/is_nan.hpp>
#include <boost/simd/include/constants/inf.hpp>
#endif


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hypot_, tag::cpu_
                                    , (A0)
                                    , ((scalar_<floating_<A0> >))
                                      ((scalar_<floating_<A0> >))
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<result_type>::type   iA0;
      #ifndef BOOST_SIMD_NO_INVALIDS
      if (is_nan(a0) && is_inf(a1)) return Inf<A0>();
      if (is_inf(a0) && is_nan(a1)) return Inf<A0>();
      #endif
      A0 r =  boost::simd::abs(a0);
      A0 i =  boost::simd::abs(a1);
      iA0 e =  exponent(boost::simd::max(i, r));
      e = boost::simd::min(boost::simd::max(e,Minexponent<A0>()),Maxexponentm1<A0>());
      return ldexp(sqrt(sqr(ldexp(r, -e))+sqr(ldexp(i, -e))), e);
    }
  };
} } }

#endif
