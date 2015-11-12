//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE4_1_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE4_1_EXTRACT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/memory/functions/extract.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse4_2_
                                    , (A0)(A1)
                                    , ((simd_< ints8_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_extract_epi8(a0, A1::value));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse4_2_
                                    , (A0)(A1)
                                    , ((simd_< ints32_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_extract_epi32(a0, A1::value));
    }
  };

#ifdef BOOST_SIMD_ARCH_X86_64
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse4_2_
                                    , (A0)(A1)
                                    , ((simd_< ints64_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      return result_type(_mm_extract_epi64(a0, A1::value));
    }
  };
#endif

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::sse4_2_
                                    , (A0)(A1)
                                    , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      float f;
      _MM_EXTRACT_FLOAT(f, a0, A1::value);
      return f;
    }
  };
} } }

#endif
#endif
