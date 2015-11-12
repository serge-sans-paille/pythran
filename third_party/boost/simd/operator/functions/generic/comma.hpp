//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_GENERIC_COMMA_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_GENERIC_COMMA_HPP_INCLUDED

#include <boost/simd/operator/functions/comma.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::comma_, tag::cpu_
                                    , (A0)(A1)
                                    , (generic_<unspecified_<A0> >)
                                      (generic_<unspecified_<A1> >)
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE result_type operator()(const A0&, const A1& a1) const
    {
      return a1;
    }
  };
} } }

#endif
