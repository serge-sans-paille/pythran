//==============================================================================
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_PERMUTATION_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_DETAILS_PERMUTATION_HPP_INCLUDED

#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/bitwise_and.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/swar/functions/details/default_permutation.hpp>
#include <boost/simd/swar/functions/simd/sse/avx/details/topology.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/permuted.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // AVX shuffle use general permutation with special case for some topology
  //============================================================================
  template<std::size_t Cardinal>
  struct avx_permutation : details::default_permutation<Cardinal>
  {};

  //============================================================================
  // Single parameters card4 permutation are handled by _mm256_shuffle_*
  //============================================================================
  template<>
  struct  avx_permutation<4>
  {
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& p)
    {
      return call(a0,p,typename details::avx_topology<P,4>::type());
    }

    // Duplicate _mm256_shuffle_pd
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0,  P const& p
                                    , details::dupe_ const&
                                    )
    {
      return call(a0,a0,p,details::direct_());
    }

    // Direct use _mm256_shuffle_pd(a0,Zero)
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::r_zero_ const&
                                    )
    {
      return call(a0,Zero<T>(),p,details::direct_());
    }

    // Direct use _mm256_shuffle_pd(Zero,a0)
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::l_zero_ const&
                                    )
    {
      return call(Zero<T>(),a0,p,details::direct_());
    }

    // Mixed just use regular hand made permutation
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::mixed_ const&
                                    )
    {
      return details::default_permutation<4>::call(a0,p);
    }

    // Two arguments check topology
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call(a0,a1,p,typename details::avx_topology<P,4>::type());
    }

    // Mixed just use regular hand made permutation
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::mixed_ const&
                                    )
    {
      return details::default_permutation<4>::call(a0,a1,p);
    }

    // blend use _mm256_blend_pd
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::blend_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;

      return bitwise_cast<T>( f_t(_mm256_blend_pd ( bitwise_cast<f_t>(a0)
                                                    , bitwise_cast<f_t>(a1)
                                                    , (details::avx_blend_mask<P,4>::value)
                                                    )
                                 )
                            );
    }

    // Direct use _mm256_shuffle_pd
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::direct_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;

      return bitwise_cast<T>( f_t(_mm256_shuffle_pd ( bitwise_cast<f_t>(a0)
                                                    , bitwise_cast<f_t>(a1)
                                                    , (details::avx_mask<P,4>::value)
                                                    )
                                 )
                            );
    }

    // Swapped _mm256_shuffle_pd
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::swap_ const&
                                    )
    {
      return call(a1,a0,p,details::direct_());
    }
  };

  template<>
  struct  avx_permutation<8>
  {
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& p)
    {
      return call(a0,p,typename details::avx_topology<P,8>::type());
    }

    // Two arguments duplicate
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::dupe_ const&
                                    )
    {
      return call(a0,a0,p,details::direct_());
    }

    // Two arguments with a 0
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::r_zero_ const&
                                    )
    {
      return call(a0,Zero<T>(),p,details::direct_());
    }

    // Two arguments with a 0
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::l_zero_ const&
                                    )
    {
      return call(Zero<T>(),a0,p,details::direct_());
    }

    // Two arguments duplicate
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, P const& p
                                    , details::mixed_ const&
                                    )
    {
      return details::default_permutation<8>::call(a0,p);
    }

    // Two arguments check topology
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call(a0,a1,p,typename details::avx_topology<P,8>::type());
    }

    // Two arguments direct
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::direct_ const&
                                    )
    {
      typedef typename dispatch::meta::as_floating<T>::type f_t;

      return bitwise_cast<T>(f_t(_mm256_shuffle_ps ( bitwise_cast<f_t>(a0)
                                                   , bitwise_cast<f_t>(a1)
                                                   , (details::avx_mask<P,8>::value)
                                                   )
                                )
                            );
    }

    // Two arguments swapped
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::swap_ const&
                                    )
    {
      return call(a1,a0,p,details::direct_());
    }

    // Two arguments mixed
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , details::mixed_ const&
                                    )
    {
      return details::default_permutation<8>::call(a0,a1,p);
    }
  };

} } }


#endif
