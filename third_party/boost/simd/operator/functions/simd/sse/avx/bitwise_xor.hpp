//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_XOR_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_BITWISE_XOR_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/bitwise_xor.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_xor_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return _mm256_xor_ps(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_xor_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      return _mm256_xor_pd(a0, a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_xor_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<integer_<A1>,boost::simd::tag::avx_>))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return _mm256_castps_si256(_mm256_xor_ps( _mm256_castsi256_ps(a0)
                                              , _mm256_castsi256_ps(a1)
                                              )
                                );
    }
  };
} } }

#endif
#endif
