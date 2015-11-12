//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_SSE2_BITWISE_CAST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/memory/functions/bitwise_cast.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< integer_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< integer_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return a0();
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< integer_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< single_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castsi128_ps(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< integer_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< double_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castsi128_pd(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< integer_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castps_si128(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< double_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< integer_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castpd_si128(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< double_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< single_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castpd_ps(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_cast_, boost::simd::tag::sse2_
                                   , (A0)(A1)
                                   , ((simd_< single_<A0>, boost::simd::tag::sse_ >))
                                     ((target_< simd_< double_<A1>, boost::simd::tag::sse_ > >))
                                   )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      return _mm_castps_pd(a0);
    }
  };
} } }

#endif
#endif
