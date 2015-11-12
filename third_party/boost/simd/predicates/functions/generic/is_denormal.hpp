//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_GENERIC_IS_DENORMAL_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_GENERIC_IS_DENORMAL_HPP_INCLUDED

#include <boost/simd/predicates/functions/is_denormal.hpp>
#include <boost/simd/include/functions/simd/is_less.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/abs.hpp>
#include <boost/simd/include/constants/false.hpp>
#include <boost/simd/include/constants/smallestposval.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_denormal_, tag::cpu_
                                   , (A0)
                                   , (generic_< arithmetic_<A0> >)
                                   )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE result_type operator()(const A0& ) const
    {
      return False<result_type>();
    }
  };
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_denormal_, tag::cpu_
                                   , (A0)
                                   , (generic_< floating_<A0> >)
                                   )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return l_and(is_nez(a0), lt(simd::abs(a0), Smallestposval<A0>()));
    }
  };
} } }


#endif
