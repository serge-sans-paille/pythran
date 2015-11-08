//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_PERMUTATION_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSE2_DETAILS_PERMUTATION_HPP_INCLUDED

#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/swar/functions/details/default_permutation.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/topology.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // SSE2 shuffle use general permutation with special case for some topology
  //============================================================================
  template<std::size_t Cardinal>
  struct sse2_permutation : details::default_permutation<Cardinal>
  {};

  //============================================================================
  // Single parameters card2 permutation are handled by _mm_shuffle_pd
  //============================================================================
  template<>
  struct  sse2_permutation<2>
  {
    // For one argument: just handle zeroing
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& p)
    {
      return call(a0,p,typename details::perform_zeroing<P,2>::type());
    }

    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , boost::mpl::true_ const&
                                    )
    {
      typedef typename dispatch::meta::as_integer<T, unsigned>::type i_t;
      T val = call(a0,p,boost::mpl::false_());

      return val & make<i_t>( details::zero_mask<char,P,0,2>::value
                            , details::zero_mask<char,P,1,2>::value
                            );
    }

    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const&
                                    , boost::mpl::false_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;
      f_t v = bitwise_cast<f_t>(a0);

      return bitwise_cast<T>( f_t(_mm_shuffle_pd (v, v
                                                 , (details::shuffle_mask<P,2>::value)
                                                 )
                                 )
                            );
    }

    // For two arguments: handle topology, all other cases are optimized already
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call(a0,a1,p,typename details::sse2_topology<P,2>::type());
    }

    // Direct shuffle requires a simple call to shuffle
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::direct_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;

      return bitwise_cast<T>( f_t(_mm_shuffle_pd( bitwise_cast<f_t>(a0)
                                                , bitwise_cast<f_t>(a1)
                                                , ( details::shuffle_mask
                                                    < details::clamp<P,2>, 2>::value
                                                  )
                                                )
                                 )
                            );
    }

    // Indirect shuffle requires swapping a0/a1 in call to shuffle
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::indirect_ const&
                                    )
    {
      return call(a1,a0,p,details::direct_());
    }
  };

  //============================================================================
  // Single parameters card4 permutation are handled by _mm_shuffle_*
  //============================================================================
  template<>
  struct  sse2_permutation<4>
  {
    // Do we perform zeroing ?
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& p)
    {
      return call(a0,p,typename details::perform_zeroing<P,4>::type());
    }

    // Yes ? Mask with proper mask vector
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , boost::mpl::true_ const&
                                    )
    {
      typedef typename dispatch::meta::as_integer<T, unsigned>::type i_t;
      T val = call(a0,p,boost::mpl::false_());

      return val & make<i_t>( details::zero_mask<char,P,0,4>::value
                            , details::zero_mask<char,P,1,4>::value
                            , details::zero_mask<char,P,2,4>::value
                            , details::zero_mask<char,P,3,4>::value
                            );
    }

    // No use proper intrinsic for single
    template<typename P>
    BOOST_FORCEINLINE static __m128 call( __m128 const& a0, P const&
                                        , boost::mpl::false_ const&
                                        )
    {
      return _mm_shuffle_ps(a0, a0, (details::shuffle_mask<P,4>::value));
    }

    // No use proper intrinsic for integers
    template<typename P>
    BOOST_FORCEINLINE static __m128i call ( __m128i const& a0, P const&
                                          , boost::mpl::false_ const&
                                          )
    {
      return _mm_shuffle_epi32(a0, (details::shuffle_mask<P,4>::value));
    }

    // Two arguments check zeroing
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call(a0,a1,p,typename details::perform_zeroing<P,4>::type());
    }

    // If we mask, mask with proper mask vector
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , boost::mpl::true_ const&
                                    )
    {
      typedef typename dispatch::meta::as_integer<T, unsigned>::type i_t;
      T val = call(a0,a1,p,boost::mpl::false_());

      return val & make<i_t>( details::zero_mask<char,P,0,4>::value
                            , details::zero_mask<char,P,1,4>::value
                            , details::zero_mask<char,P,2,4>::value
                            , details::zero_mask<char,P,3,4>::value
                            );
    }

    // If not, inspect the permutation topology
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , boost::mpl::false_ const&
                                    )
    {
      return call(a0,a1,p,typename details::sse2_topology<P,4>::type());
    }

    // Mixed just use regular hand made permutation
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::mixed_ const&
                                    )
    {
      return details::default_permutation<4>::call(a0,a1,p);
    }

    // Direct use _mm_shuffle_ps
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::direct_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;

      return bitwise_cast<T>( f_t(_mm_shuffle_ps( bitwise_cast<f_t>(a0)
                                                , bitwise_cast<f_t>(a1)
                                                , (details::shuffle_mask
                                                    <details::clamp<P,4>, 4>::value
                                                  )
                                                )
                                 )
                            );
    }

    // Indirect is direct with a0/a1 swapped
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::indirect_ const&
                                    )
    {
      return call(a1,a0,p,details::direct_());
    }
  };
} } }

#endif
