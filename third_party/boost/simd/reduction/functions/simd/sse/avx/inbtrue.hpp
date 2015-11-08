//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_INBTRUE_HPP_INCLUDED
#define BOOST_SIMD_REDUCTION_FUNCTIONS_SIMD_SSE_AVX_INBTRUE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/reduction/functions/inbtrue.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::inbtrue_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<arithmetic_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef std::size_t result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      typedef typename meta::scalar_of<A0>::type sctype;
      typedef simd::native<sctype, boost::simd::tag::sse_ >  svtype;
      svtype a00 = _mm256_extractf128_si256(a0, 0);
      svtype a01 = _mm256_extractf128_si256(a0, 1);
      return inbtrue(a00)+inbtrue(a01);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::inbtrue_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<double_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef std::size_t result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      std::size_t  r = _mm256_movemask_pd(is_nez(a0));
      return   (r&1)+(r>>1&1)+((r>>2)&1)+(r>>3);
    }
  };

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::inbtrue_, boost::simd::tag::avx_,
                         (A0),
                         ((simd_<single_<A0>,boost::simd::tag::avx_>))
                        )
  {
    typedef std::size_t result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(1)
    {
      std::size_t  r = _mm256_movemask_ps(is_nez(a0));
      return   (r&1)+((r>>1)&1)+((r>>2)&1)+(r>>3&1)+((r>>4)&1)+((r>>5)&1)+(r>>6&1)+(r>>7);
      //      typedef typename dispatch::meta::as_floating<A0>::type type;
      //      return __builtin_popcount(_mm_movemask_ps(isnez(cast<type>(a0))));
    }
  };
} } }
#endif
#endif
