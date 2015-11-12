//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE4_1_INSERT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE4_1_INSERT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE4_1_SUPPORT

#include <boost/simd/memory/functions/insert.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , (scalar_< integer_<A0> >)
                                      ((simd_< ints8_<A1>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A2> > >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2) const
    {
      a1 = _mm_insert_epi8(a1, a0, A2::value);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , (scalar_< integer_<A0> >)
                                      ((simd_< ints32_<A1>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A2> > >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2) const
    {
      a1 = _mm_insert_epi32(a1, a0, A2::value);
    }
  };

#ifdef BOOST_SIMD_ARCH_X86_64
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::insert_
                                    , boost::simd::tag::sse2_
                                    , (A0)(A1)(A2)
                                    , (scalar_< integer_<A0> >)
                                      ((simd_< ints64_<A1>, boost::simd::tag::sse_ >))
                                      (mpl_integral_< scalar_< integer_<A2> > >)
                                    )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1& a1, A2) const
    {
      a1 = _mm_insert_epi64(a1, a0, A2::value);
    }
  };
#endif

} } }

#endif
#endif
