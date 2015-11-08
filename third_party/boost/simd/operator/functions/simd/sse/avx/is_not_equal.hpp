//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_IS_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_IS_NOT_EQUAL_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/is_not_equal.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_not_equal_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm256_cmp_pd(a0,a1, _CMP_NEQ_UQ);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_not_equal_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                      ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm256_cmp_ps(a0,a1, _CMP_NEQ_UQ);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_not_equal_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmp_pd(a0,a1, _CMP_NEQ_UQ);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_not_equal_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmp_ps(a0,a1, _CMP_NEQ_UQ);
    }
  };
} } }

#endif
#endif
