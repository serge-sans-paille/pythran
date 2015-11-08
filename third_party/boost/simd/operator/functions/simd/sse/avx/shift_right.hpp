//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SHIFT_RIGHT_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_SHIFT_RIGHT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/shift_right.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::shift_right_, boost::simd::tag::avx_
                            , (A0)(A1)
                            , ((simd_<integer_<A0>,boost::simd::tag::avx_>))
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type                   stype;
      typedef simd::native<stype, boost::simd::tag::sse_ >        svtype;

      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      A0 that = _mm256_castsi128_si256(boost::simd::shift_right(a00, a1));
      return _mm256_insertf128_si256(that, boost::simd::shift_right(a01, a1), 1);
     }
  };
} } }

#endif
#endif
