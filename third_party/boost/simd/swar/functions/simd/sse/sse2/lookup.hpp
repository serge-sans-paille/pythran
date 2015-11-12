//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT
#include <boost/simd/swar/functions/lookup.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/meta/size.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/simd/preprocessor/aligned_type.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::lookup_, boost::simd::tag::sse2_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,boost::simd::tag::sse_>))((simd_<integer_<A1>,boost::simd::tag::sse_>))
                            )
  {

    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      BOOST_SIMD_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
      BOOST_SIMD_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
      boost::simd::aligned_store<A0>(a0, &tmp[0], 0);

      for(unsigned int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
      return boost::simd::aligned_load<A0>(&tmp1[0], 0);
    }
  };
} } }



#endif
#endif
