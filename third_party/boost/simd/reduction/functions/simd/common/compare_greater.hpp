//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_GREATER_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_COMMON_COMPARE_GREATER_HPP_INCLUDED

#include <boost/simd/reduction/functions/compare_greater.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/simd/include/functions/simd/compare_less.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::compare_greater_
                                    , tag::cpu_, (X)(A0)
                                    , ((simd_<arithmetic_<A0>,X>))
                                      ((simd_<arithmetic_<A0>,X>))
                                    )
  {
    typedef typename meta::scalar_of<A0>::type  sA0;
    typedef typename meta::as_logical<sA0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return compare_less(a1, a0);
    }
  };
} } }

#endif
