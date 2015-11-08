//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_LESS_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_LESS_HPP_INCLUDED

#include <boost/simd/reduction/functions/compare_less.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::compare_less_, tag::cpu_, (A0)(X)
                      , ((simd_<arithmetic_<A0>,X>))
                        ((simd_<arithmetic_<A0>,X>))
                      )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      for(std::size_t i=0;i<boost::simd::meta::cardinal_of<A0>::value;++i)
      {
        if (a0[i] < a1[i])  return result_type(true);
        if (a1[i] < a0[i])  return result_type(false);
      }
      return result_type(false);
    }
  };
} } }

#endif
