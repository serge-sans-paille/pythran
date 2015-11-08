//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_INTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_INTERLEAVE_SECOND_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/interleave_second.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_floating.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      // 0x31 is SCR1[128:255]|SRC2[128:255] according to Intel AVX manual
      // The result of unpack_*_ps puts parts in the proper pairs beforehand
      return _mm256_permute2f128_ps ( _mm256_unpacklo_ps(a0,a1)
                                    , _mm256_unpackhi_ps(a0,a1)
                                    , 0x31
                                    );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::interleave_second_
                                   , boost::simd::tag::avx_
                                   , (A0)
                                   , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                     ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      // workaround for bad ICC optimisation
      #ifdef __INTEL_COMPILER
      __m256d volatile lo = _mm256_unpacklo_pd(a0,a1);
      #else
      __m256d lo = _mm256_unpacklo_pd(a0,a1);
      #endif

      // 0x31 is SCR1[128:255]|SRC2[128:255] according to Intel AVX manual
      // The result of unpack_*_pd puts parts in the proper pairs beforehand
      return _mm256_permute2f128_pd ( lo
                                    , _mm256_unpackhi_pd(a0,a1)
                                    , 0x31
                                    );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::interleave_second_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < floating_sized_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      ((simd_ < floating_sized_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                   )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A0 const& a1) const
    {
      typedef typename boost::dispatch::meta::as_floating<A0>::type  ftype;
      return  bitwise_cast<result_type>
              ( interleave_second ( bitwise_cast<ftype>(a0)
                                  , bitwise_cast<ftype>(a1)
                                  )
              );
    }
  };
} } }

#endif
#endif
