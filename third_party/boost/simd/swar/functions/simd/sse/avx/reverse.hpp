//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_REVERSE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_REVERSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/reverse.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      return _mm256_permute_pd( _mm256_permute2f128_pd(a0,a0,1), 5 );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < ints64_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type f_t;
      return  bitwise_cast<A0>(reverse(bitwise_cast<f_t>(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      A0 tmp = _mm256_permute_ps(a0, _MM_SHUFFLE(0,1,2,3) );
      return _mm256_permute2f128_ps(tmp,tmp,1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < ints32_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename dispatch::meta::as_floating<A0>::type f_t;
      return  bitwise_cast<A0>(reverse(bitwise_cast<f_t>(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::reverse_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_ < arithmetic_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                    )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::retarget<A0, boost::simd::tag::sse_ >::type  s_t;

      s_t a000 = _mm256_extractf128_si256(a0, 0);
      s_t a011 = _mm256_extractf128_si256(a0, 1);

      return _mm256_insertf128_si256( _mm256_castsi128_si256( reverse(a011) )
                                    , reverse(a000)
                                    , 1
                                    );
    }
  };
} } }

#endif
#endif
