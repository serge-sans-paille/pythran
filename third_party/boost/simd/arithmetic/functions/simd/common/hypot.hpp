//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_COMMON_HYPOT_HPP_INCLUDED

#include <boost/simd/arithmetic/functions/hypot.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/functions/simd/min.hpp>
#include <boost/simd/include/functions/simd/max.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/unary_minus.hpp>
#include <boost/simd/include/functions/simd/exponent.hpp>
#include <boost/simd/include/functions/simd/ldexp.hpp>
#include <boost/simd/include/functions/simd/sqr.hpp>
#include <boost/simd/include/functions/simd/sqrt.hpp>
#include <boost/simd/include/constants/maxexponentm1.hpp>
#include <boost/simd/include/constants/minexponent.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

#ifndef BOOST_SIMD_NO_INVALIDS
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/is_inf.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/constants/inf.hpp>
#endif


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hypot_, tag::cpu_
                                    , (A0)(X)
                                    , ((simd_<floating_<A0>,X>))
                                      ((simd_<floating_<A0>,X>))
                                    )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<result_type>::type   iA0;
      result_type r =  boost::simd::abs(a0);
      result_type i =  boost::simd::abs(a1);
      iA0 e =  exponent(boost::simd::max(i, r));
      e = boost::simd::min(boost::simd::max(e,Minexponent<A0>()),Maxexponentm1<A0>());
      result_type res =  ldexp(sqrt(sqr(ldexp(r, -e))+sqr(ldexp(i, -e))), e);
      #ifndef BOOST_SIMD_NO_INVALIDS
      typedef typename meta::as_logical<result_type>::type             lA0;
      lA0 test = logical_or(logical_and(is_nan(a0), is_inf(a1)),
                            logical_and(is_nan(a1), is_inf(a0)));
      return if_else(test, Inf<result_type>(), res);
      #else
      return res;
      #endif
    }
  };
} } }

#endif
