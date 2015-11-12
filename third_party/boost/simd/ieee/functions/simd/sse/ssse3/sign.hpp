//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_IEEE_FUNCTIONS_SIMD_SSE_SSSE3_SIGN_HPP_INCLUDED
#define BOOST_SIMD_IEEE_FUNCTIONS_SIMD_SSE_SSSE3_SIGN_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSSE3_SUPPORT
#include <boost/simd/ieee/functions/sign.hpp>
#include <boost/simd/ieee/functions/simd/common/sign.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sign_, boost::simd::tag::ssse3_,
                       (A0),
                       ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return _mm_sign_epi32(One<A0>(), a0);  }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sign_, boost::simd::tag::ssse3_,
                       (A0),
                       ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return _mm_sign_epi16(One<A0>(), a0);  }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::sign_, boost::simd::tag::ssse3_,
                       (A0),
                       ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                      )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1) { return _mm_sign_epi8(One<A0>(), a0);  }
  };
} } }
#endif
#endif
