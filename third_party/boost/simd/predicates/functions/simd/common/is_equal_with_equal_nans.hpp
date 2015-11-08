//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#define BOOST_SIMD_PREDICATES_FUNCTIONS_SIMD_COMMON_IS_EQUAL_WITH_EQUAL_NANS_HPP_INCLUDED
#include <boost/simd/predicates/functions/is_equal_with_equal_nans.hpp>
#include <boost/simd/include/functions/simd/is_nan.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::is_equal_with_equal_nans_, tag::cpu_
                            , (A0)(X)
                            , ((simd_<floating_<A0>,X>))((simd_<floating_<A0>,X>))
                            )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return logical_or(eq(a0,a1), logical_and(boost::simd::is_nan(a0), boost::simd::is_nan(a1)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::is_equal_with_equal_nans_, tag::cpu_,
           (A0)(X),
           ((simd_<fundamental_<A0>,X>))
           ((simd_<fundamental_<A0>,X>))
           )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return eq(a0,a1);
    }
  };
} } }

#endif
