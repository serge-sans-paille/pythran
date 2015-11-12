//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_PATTERNS_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_PATTERNS_HPP_INCLUDED

#include <boost/simd/swar/functions/details/shuffle.hpp>
#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/swar/functions/details/interleave_pattern.hpp>
#include <boost/simd/swar/functions/details/broadcast_pattern.hpp>
#include <boost/simd/swar/functions/details/identity_pattern.hpp>
#include <boost/simd/swar/functions/details/reverse_pattern.hpp>
#include <boost/simd/swar/functions/details/repeat_pattern.hpp>
#include <boost/simd/swar/functions/details/zero_pattern.hpp>
#include <boost/simd/swar/functions/details/slide_pattern.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // SSE2 shuffle use the general pattern matcher optimizer with some specific
  // patterns tied to SSE2 intrinsics.
  //============================================================================
  struct sse2_matcher
  {
    // This is true for w/e cardinal
    template<int I0, int I1, typename Permutation>
    struct match2 : details::default_matcher::match2<I0,I1,Permutation>
    {};

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

    template< int I0 , int I1 , int I2 , int I3
            , int I4 , int I5 , int I6 , int I7
            , int I8 , int I9 , int I10, int I11
            , int I12, int I13, int I14, int I15
            , typename Permutation
            >
    struct match16 : details::default_matcher
                            ::match16 < I0, I1, I2 , I3 , I4 , I5 , I6 , I7
                                      , I8, I9, I10, I11, I12, I13, I14, I15
                                      , Permutation
                                      >
    {};
  };

  //============================================================================
  // Optimized cardinal 2 pattern + zeroing
  //============================================================================
  template<typename Permutation>
  struct sse2_matcher::match2<-1,0,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_integer<T>::type i_t;
      return bitwise_cast<T>(i_t(_mm_slli_si128( bitwise_cast<i_t>(a0), 8)));
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match2<1,-1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_integer<T>::type i_t;
      return bitwise_cast<T>(i_t(_mm_srli_si128( bitwise_cast<i_t>(a0), 8)));
    }
  };

  //============================================================================
  // Optimized cardinal 4 pattern
  //============================================================================
  template<typename Permutation>
  struct sse2_matcher::match4<0,1,4,5,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0,T const& a1, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>(f_t( _mm_movelh_ps ( bitwise_cast<f_t>(a0)
                                                , bitwise_cast<f_t>(a1)
                                                )
                                )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<4,5,0,1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0,T const& a1, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movelh_ps ( bitwise_cast<f_t>(a1)
                                                , bitwise_cast<f_t>(a0)
                                                )
                                 )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<2,3,6,7,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0,T const& a1, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movehl_ps ( bitwise_cast<f_t>(a1)
                                                , bitwise_cast<f_t>(a0)
                                                )
                                 )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<6,7,2,3,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0,T const& a1, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movehl_ps ( bitwise_cast<f_t>(a0)
                                               , bitwise_cast<f_t>(a1)
                                               )
                                 )
                            );
    }
  };

  //============================================================================
  // Optimized cardinal 4 pattern + zeroing
  //============================================================================
  template<typename Permutation>
  struct sse2_matcher::match4<0,1,-1,-1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movelh_ps ( bitwise_cast<f_t>(a0)
                                                , Zero<f_t>()
                                                )
                                 )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<2,3,-1,-1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movehl_ps ( Zero<f_t>()
                                                , bitwise_cast<f_t>(a0)
                                                )
                                 )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<-1,-1,0,1,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movelh_ps ( Zero<f_t>()
                                                , bitwise_cast<f_t>(a0)
                                                )
                                 )
                            );
    }
  };

  template<typename Permutation>
  struct sse2_matcher::match4<-1,-1,2,3,Permutation>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename boost::dispatch::meta::as_floating<T>::type f_t;
      return bitwise_cast<T>( f_t(_mm_movehl_ps ( bitwise_cast<f_t>(a0)
                                                , Zero<f_t>()
                                                )
                                 )
                            );
    }
  };
} } }

#endif
