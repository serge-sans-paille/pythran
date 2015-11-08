//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED
#define BOOST_SIMD_DSL_FUNCTIONS_GENERIC_EVALUATE_HPP_INCLUDED

#include <boost/simd/dsl/functions/evaluate.hpp>
#include <boost/simd/include/functions/run.hpp>

#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::evaluate_
                                    , tag::formal_
                                    , (A0)(D)
                                    , ((ast_<A0, D>))
                                    )
  {
    typedef typename dispatch::meta::call<tag::run_(A0&)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0& a0) const
    {
      return run(a0);
    }
  };
} } }

#endif
