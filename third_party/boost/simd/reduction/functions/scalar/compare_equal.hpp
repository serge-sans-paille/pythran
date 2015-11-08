//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_COMPARE_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SCALAR_COMPARE_EQUAL_HPP_INCLUDED

#include <boost/simd/reduction/functions/compare_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::compare_equal_
                                    , tag::cpu_
                                    , (A0)
                                    , (scalar_< arithmetic_<A0> >)
                                      (scalar_< arithmetic_<A0> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, A0 a1) const
    {
      return result_type(a0 == a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::compare_equal_
                                    , tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< fundamental_<A0> >)
                                      (scalar_< fundamental_<A1> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(bool(a0) == bool(a1)) ;
    }
  };
} } }

#endif
