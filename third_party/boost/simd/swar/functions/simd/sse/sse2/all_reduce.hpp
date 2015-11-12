//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_ALL_REDUCE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/swar/functions/all_reduce.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::sse2_
                                    , (Tag)(A0)
                                    , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      // Buttefly reduction optimized for int16
      dispatch::functor<base> op;

      A0 a1 = _mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2));
      result_type t1 = op(a0,a1);
      result_type t2 = _mm_shuffle_epi32(t1, _MM_SHUFFLE(2, 3, 0, 1));
                  t2 = op(t2, t1);

      t1 = _mm_shufflehi_epi16(t2, _MM_SHUFFLE(0, 1, 2, 3));
      t1 = _mm_shufflelo_epi16(t1, _MM_SHUFFLE(0, 1, 2, 3));

      return op(t2, t1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::sse2_
                                    , (Tag)(A0)
                                    , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;


    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      // Buttefly reduction optimized for int8
      dispatch::functor<base> op;

      // 16 -> 2x8
      A0          a1 = _mm_shuffle_epi32(a0, _MM_SHUFFLE(1, 0, 3, 2));
      result_type t1 = op(a0,a1);

      // 2x8 -> 4x4
      result_type t2 = _mm_shuffle_epi32(t1, _MM_SHUFFLE(2, 3, 0, 1));
                  t2 = op(t2, t1);

      // 4x4 -> 8x2
      t1 = _mm_shufflehi_epi16(t2, _MM_SHUFFLE(0, 1, 2, 3));
      t1 = _mm_shufflelo_epi16(t1, _MM_SHUFFLE(0, 1, 2, 3));
      t1 = op(t2,t1);

      // Reorder [ a b ... a b ] into [ a a b b ... a a b b]
      t1 = _mm_unpacklo_epi8(t1,t1);
      t1 = _mm_unpackhi_epi8(t1,t1);

      // Turn [ a a b b ... a a b b] into [ b b a a ... b b a a]
      t2 = _mm_shufflehi_epi16(t1, _MM_SHUFFLE(0, 1, 2, 3));
      t2 = _mm_shufflelo_epi16(t2, _MM_SHUFFLE(0, 1, 2, 3));

      return op(t2, t1);
    }
  };
} } }

#endif

#endif
