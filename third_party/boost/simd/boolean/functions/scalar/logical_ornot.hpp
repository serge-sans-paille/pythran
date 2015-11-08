//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_BOOLEAN_FUNCTIONS_SCALAR_LOGICAL_ORNOT_HPP_INCLUDED
#include <boost/simd/boolean/functions/logical_ornot.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::logical_ornot_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< unspecified_<A0> >)
                                      (scalar_< unspecified_<A1> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(a0 || !a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::logical_ornot_, tag::cpu_
                                    , (A0)(A1)
                                    , (scalar_< logical_<A0> >)
                                      (scalar_< logical_<A1> >)
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return result_type(a0.value() || !a1.value());
    }
  };
} } }

#endif

