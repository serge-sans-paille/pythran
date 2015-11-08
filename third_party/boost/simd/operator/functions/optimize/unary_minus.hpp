//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_OPTIMIZE_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_OPTIMIZE_UNARY_MINUS_HPP_INCLUDED

#include <boost/simd/operator/functions/unary_minus.hpp>
#include <boost/simd/arithmetic/functions/fma.hpp>
#include <boost/simd/arithmetic/functions/fms.hpp>
#include <boost/simd/include/functions/fnma.hpp>
#include <boost/simd/include/functions/fnms.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unary_minus_ , tag::formal_, (D)(A0)
                                   , ((node_<A0, boost::simd::tag::fma_, mpl::long_<3> , D>))
                                   )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      fnma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), boost::proto::child_c<2>(a0))
    )
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unary_minus_ , tag::formal_, (D)(A0)
                                   , ((node_<A0, boost::simd::tag::fms_, mpl::long_<3> , D>))
                                   )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& a0),
      fnms(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), boost::proto::child_c<2>(a0))
    )
  };
} } }

#endif
