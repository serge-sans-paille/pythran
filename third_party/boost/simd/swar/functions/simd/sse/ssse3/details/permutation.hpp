//==============================================================================
//         Copyright 2009 - 2014 LRI UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NumScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_DETAILS_PERMUTATION_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_SSSE3_DETAILS_PERMUTATION_HPP_INCLUDED

#include <boost/simd/include/functions/simd/bitwise_or.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/permutation.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/topology.hpp>
#include <boost/simd/swar/functions/simd/sse/sse2/details/patterns.hpp>
#include <boost/simd/swar/functions/details/topology.hpp>
#include <boost/simd/swar/functions/details/perm.hpp>
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
  struct sse3_permutation
  {
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, P const& )
    {
      typedef typename T::template rebind<unsigned char>::type m_t;
      m_t const that = _mm_shuffle_epi8( bitwise_cast<m_t>(a0)
                                       , details::permute<P,m_t,Cardinal>::call()
                                       );
      return bitwise_cast<T>(that);
    }

    template<typename T, typename P>
    BOOST_FORCEINLINE static T call(T const& a0, T const& a1, P const& p)
    {
      return call ( a0,a1,p
                  , typename details::sse2_topology<P,Cardinal>::type()
                  );
    }

    // All shuffle uses SSE2 if possible
    template<typename T, typename P, typename Topology>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , Topology const& t
                                    )
    {
      static const bool is_sse2_supported = Cardinal <= 4;
      return call(a0,a1,p,t,boost::mpl::bool_<is_sse2_supported>());
    }

    // All shuffle uses SSE2 if possible
    template<typename T, typename P, typename Topology>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , Topology const&
                                    , boost::mpl::true_ const&
                                    )
    {
      return sse2_permutation<Cardinal>::call(a0,a1,p);
    }

    // If not go for byte permute
    template<typename T, typename P, typename Topology>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const& p
                                    , Topology const&
                                    , boost::mpl::false_ const&
                                    )
    {
      return call ( a0, a1, p, details::indirect_() );
    }

    // Keep a0 indexing, zero out the other
    template<typename P> struct force_left
    {
      template<typename I, typename C> struct apply
      {
        typedef typename boost::mpl::apply<P,I,C>::type base_t;

        //  make -1 if it was outside [0,C[ and let as if if inside
        typedef boost::mpl::int_< !(base_t::value >= C::value)
                                ? base_t::value
                                : -1
                                >                       type;
      };
    };

    // Keep a1 reduced indexing, zero out the other
    template<typename P> struct force_right
    {
      template<typename I, typename C> struct apply
      {
        typedef typename boost::mpl::apply<P,I,C>::type base_t;

        //  make -1 if it was inside [0,C[ and shift if outside
        typedef boost::mpl::int_< (base_t::value >= C::value)
                                ? (base_t::value - C::value)
                                : -1
                                >                       type;
      };
    };

    // Indirect shuffle requires swapping a0/a1 in call to shuffle
    template<typename T, typename P>
    BOOST_FORCEINLINE static T call ( T const& a0, T const& a1, P const&
                                    , details::indirect_ const&
                                    )
    {
      // double permute + bitwise or
      return  call(a0, force_left <P>() ) | call(a1, force_right<P>() );
    }
  };
} } }

#endif
