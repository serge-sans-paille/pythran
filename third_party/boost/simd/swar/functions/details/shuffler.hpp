//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_SHUFFLER_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_DETAILS_SHUFFLER_HPP_INCLUDED

#include <boost/simd/swar/functions/details/default_permutation.hpp>
#include <boost/simd/swar/functions/details/interleave_pattern.hpp>
#include <boost/simd/swar/functions/details/broadcast_pattern.hpp>
#include <boost/simd/swar/functions/details/reverse_pattern.hpp>
#include <boost/simd/swar/functions/details/identity_pattern.hpp>
#include <boost/simd/swar/functions/details/repeat_pattern.hpp>
#include <boost/simd/swar/functions/details/default_matcher.hpp>
#include <boost/simd/swar/functions/details/slide_pattern.hpp>
#include <boost/simd/swar/functions/details/zero_pattern.hpp>
#include <boost/simd/swar/functions/details/filler.hpp>
#include <boost/simd/include/functions/simd/aligned_load.hpp>
#include <boost/dispatch/attributes.hpp>

#include <boost/preprocessor/repetition/enum.hpp>

#define M0(z,idx,card) permuted<P,idx,card>::value                             \
/**/

#define R0(z,idx,card) permuted< remap<P,card>,idx,card>::value                \
/**/

#define M1(z,card,t)                                                           \
template<typename Matcher, typename Permutation, std::size_t MaxCardinal>      \
struct shuffler<Matcher, Permutation, card, MaxCardinal, true>                 \
{                                                                              \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE T process(T const& a0, P const& p)                  \
  {                                                                            \
    typedef typename Matcher::template                                         \
            BOOST_PP_CAT(match,card)< BOOST_PP_ENUM(card,M0,card)              \
                                    , Permutation                              \
                                    > m_t;                                     \
                                                                               \
    return m_t::process(a0,p);                                                 \
  }                                                                            \
                                                                               \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const& p)     \
  {                                                                            \
    return process(a0,a1,p,typename topology<P,card>::type());                 \
  }                                                                            \
                                                                               \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE                                                     \
  T process(T const& a0, T const&, P const& p, first_arg const&)               \
  {                                                                            \
    typedef typename Matcher::template                                         \
            BOOST_PP_CAT(match,card)< BOOST_PP_ENUM(card,M0,card)              \
                                    , Permutation                              \
                                    > m_t;                                     \
                                                                               \
    return m_t::process(a0,p);                                                 \
  }                                                                            \
                                                                               \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE                                                     \
  T process(T const&, T const& a1, P const&, second_arg const&)                \
  {                                                                            \
    typedef typename Matcher::template                                         \
            BOOST_PP_CAT(match,card)< BOOST_PP_ENUM(card,R0,card)              \
                                    , Permutation                              \
                                    > m_t;                                     \
                                                                               \
    return m_t::process(a1,remap<P,card>());                                   \
  }                                                                            \
                                                                               \
  template<typename T, typename P>                                             \
  static BOOST_FORCEINLINE                                                     \
  T process(T const& a0, T const& a1, P const& p, mixed_arg const&)            \
  {                                                                            \
    typedef typename Matcher::template                                         \
            BOOST_PP_CAT(match,card)< BOOST_PP_ENUM(card,M0,card)              \
                                    , Permutation                              \
                                    > m_t;                                     \
                                                                               \
    return m_t::process(a0,a1,p);                                              \
  }                                                                            \
};                                                                             \
/**/

namespace boost { namespace simd { namespace details
{
  //============================================================================
  // shuffler is a decentralized shuffle pattern solver
  // Shuffling try to match an optimized pattern via Matcher and if it fails,
  // use the generic Permutation functor to perform the shuffling.
  //============================================================================
  template< typename Matcher, typename Permutation
          , std::size_t Cardinal
          , std::size_t MaxCardinal
          , bool useMatcher = (Cardinal <= MaxCardinal)
          >
  struct shuffler;

  BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM(2,M1,~)

  //============================================================================
  // As some extensions only handles some type of permutation, shuffler is
  // parametrized by a maximum Cardinal after which it will default to do
  // aligned_load over an aligned_array filled with proper values.
  //============================================================================
  template< typename Matcher, typename Permutation
          , std::size_t Cardinal
          , std::size_t MaxCardinal
          >
  struct shuffler<Matcher, Permutation, Cardinal, MaxCardinal, false>
  {
    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, P const&)
    {
      typedef typename meta::scalar_of<T>::type                       s_t;
      typedef aligned_array<s_t,Cardinal,BOOST_SIMD_CONFIG_ALIGNMENT> data_t;

      data_t that;
      meta::iterate<Cardinal>( unary_filler<data_t,T,P>(a0,that) );

      return aligned_load<T>(&that[0]);
    }

    template<typename T, typename P>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, P const&)
    {
      typedef typename meta::scalar_of<T>::type                       s_t;
      typedef aligned_array<s_t,Cardinal,BOOST_SIMD_CONFIG_ALIGNMENT> data_t;

      data_t that;
      meta::iterate<Cardinal>( binary_filler<data_t,T,P>(a0,a1,that) );

      return aligned_load<T>(&that[0]);
    }
  };
} } }

#undef R0
#undef M0
#undef M1

#endif
