//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_PATTERNS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_PATTERNS_HPP_INCLUDED

#include <boost/simd/swar/functions/details/shuffle.hpp>
#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/swar/functions/details/interleave_pattern.hpp>
#include <boost/simd/swar/functions/details/broadcast_pattern.hpp>
#include <boost/simd/swar/functions/details/identity_pattern.hpp>
#include <boost/simd/swar/functions/details/reverse_pattern.hpp>
#include <boost/simd/swar/functions/details/repeat_pattern.hpp>
#include <boost/simd/swar/functions/details/slide_pattern.hpp>
#include <boost/simd/swar/functions/details/zero_pattern.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // AVX use the default_matcher + special cases for 4-8
  //============================================================================
  struct avx_matcher
  {
    template< int I0, int I1, int I2, int I3, typename Permutation>
    struct match4 : details::default_matcher::match4<I0,I1,I2,I3,Permutation>
    {};

    template< int I0, int I1, int I2, int I3
            , int I4, int I5, int I6, int I7
            , typename Permutation
            >
    struct match8 : details::default_matcher
                           ::match8 < I0, I1, I2, I3, I4, I5, I6, I7
                                    , Permutation
                                    >
    {};
  };

  //============================================================================
  // AVX optimized case for cardinal 4
  //============================================================================
  template<typename Permutation>
  struct avx_matcher::match4<0,0,2,2,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type i_t;
      return bitwise_cast<T>(i_t(_mm256_movedup_pd( bitwise_cast<i_t>(a0) )));
    }
  };

  //============================================================================
  // AVX optimized case for cardinal 8
  //============================================================================
  template<typename Permutation>
  struct avx_matcher::match8<0,0,2,2,4,4,6,6,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type i_t;
      return bitwise_cast<T>(i_t(_mm256_moveldup_ps( bitwise_cast<i_t>(a0) )));
    }
  };

  template<typename Permutation>
  struct avx_matcher::match8<1,1,3,3,5,5,7,7,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type i_t;
      return bitwise_cast<T>(i_t(_mm256_movehdup_ps( bitwise_cast<i_t>(a0) )));
    }
  };
} } }

#endif
