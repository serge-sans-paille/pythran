//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_QPX_PLUS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_VMX_QPX_PLUS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_QPX_SUPPORT

#include <boost/simd/operator/functions/plus.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_, boost::simd::tag::qpx_
                                   , (A0)
                                   , ((simd_<double_<A0>, boost::simd::tag::qpx_>))
                                     ((simd_<double_<A0>, boost::simd::tag::qpx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return vec_add(a0(), a1());
    }
  };
} } }

#endif
#endif
