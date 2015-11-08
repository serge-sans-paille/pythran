//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOINT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/arithmetic/functions/toint.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toint_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return make<result_type>(a0[0], a0[1], a0[2], a0[3]);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::toint_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_integer<A0>::type result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm256_cvttps_epi32(a0);
    }
  };
} } }

#endif
#endif
