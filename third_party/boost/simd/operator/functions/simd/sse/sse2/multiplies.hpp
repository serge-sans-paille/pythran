//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/operator/functions/multiplies.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_mul_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_mul_ps(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints8_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0,signed>::type  type;
      type mask = integral_constant<type,0x00FF>();

      return _mm_or_si128 ( _mm_and_si128(mask, _mm_mullo_epi16(a0,a1))
                          , _mm_slli_epi16
                            ( _mm_and_si128 ( mask
                                            , _mm_mullo_epi16
                                              ( _mm_srli_epi16(a0(), 8)
                                              , _mm_srli_epi16(a1(), 8)
                                              )
                                            )
                            , 8
                            )
                          );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints16_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_mullo_epi16(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::multiplies_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<ints32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef A0 result_type;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif // __clang__

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_or_si128(
                    _mm_and_si128(
                       _mm_mul_epu32(a0,a1),
                       _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
                    )
                  , _mm_slli_si128(
                        _mm_and_si128(
                            _mm_mul_epu32( _mm_srli_si128(a0,4)
                                         , _mm_srli_si128(a1,4)
                                         )
                          , _mm_setr_epi32(0xffffffff,0,0xffffffff,0)
                        )
                      , 4
                    )
             );
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

  };
} } }

#endif
#endif
