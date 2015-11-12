//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_HMSB_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_HMSB_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/reduction/functions/hmsb.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/shift_left.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>
#include <cstddef>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < type8_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::retarget<A0, boost::simd::tag::sse_>::type r_t;

      r_t a00 = _mm256_extractf128_si256(a0, 0);
      r_t a01 = _mm256_extractf128_si256(a0, 1);

      return      result_type(_mm_movemask_epi8(a00))
              | ( result_type(_mm_movemask_epi8(a01)) << 16 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < type16_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename meta::retarget<A0, boost::simd::tag::sse_>::type r_t;

      r_t a00 = _mm256_extractf128_si256(a0, 0);
      r_t a01 = _mm256_extractf128_si256(a0, 1);

      return hmsb(a00) | (hmsb(a01)<<8);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type vfloat;
      return _mm256_movemask_ps(bitwise_cast<vfloat>(a0));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::hmsb_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef std::size_t result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type vdouble;
      return _mm256_movemask_pd(bitwise_cast<vdouble>(a0));
    }
  };
} } }

#endif
#endif
