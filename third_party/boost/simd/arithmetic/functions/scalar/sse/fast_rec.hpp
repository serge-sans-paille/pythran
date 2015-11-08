//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_FAST_REC_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SCALAR_SSE_FAST_REC_HPP_INCLUDED
#if defined(BOOST_SIMD_HAS_SSE2_SUPPORT)

#include <boost/simd/arithmetic/functions/fast_rec.hpp>
#include <boost/simd/include/functions/scalar/refine_rec.hpp>
#include <boost/simd/include/functions/scalar/raw_rec.hpp>
#include <boost/simd/sdk/config.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rec_
                                    , boost::simd::tag::sse_
                                    , (A0)
                                    , (scalar_< single_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      return refine_rec(a0, raw_rec( a0 ));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::fast_rec_
                                    , boost::simd::tag::sse_
                                    , (A0)
                                    , (scalar_< double_<A0> >)
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0) const
    {
      float x  = a0;
      double e = static_cast<float>(raw_rec( x ));
             e = refine_rec(a0, e);

      return refine_rec(a0, e);
    }
  };
} } }

#endif
#endif
