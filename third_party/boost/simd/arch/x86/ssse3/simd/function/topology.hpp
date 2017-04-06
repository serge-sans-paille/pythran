//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSSE3_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/arch/x86/sse1/simd/function/topology.hpp>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // SSSE3 shuffling patterns
  struct ssse3_shuffle : sse1_shuffle
  {
    using sse1_shuffle::process;

    // Unary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<Ps...> const&)
    {
      using bytes_t   = typename T::template retype<std::uint8_t,16>;
      using ranges_t  = nsm::range<int,0,16>;
      using pattern_t = nsm::integral_list<int,Ps...>;

      return  bitwise_cast<T>
        ( bytes_t( _mm_shuffle_epi8( bitwise_cast<bytes_t>(a0)
                                , detail::mask_all<16/T::static_size>( ranges_t{}, pattern_t{} )
                                )
                 )
              );
    }

    // Binary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<Ps...> const&)
    {
      using bytes_t   = typename T::template retype<std::uint8_t,16>;
      using ranges_t  = nsm::range<int,0,16>;
      using pattern_t = nsm::integral_list<int,Ps...>;

      return  bitwise_or
        ( bitwise_cast<T>(bytes_t
                ( _mm_shuffle_epi8( bitwise_cast<bytes_t>(a0)
                                  , detail::mask_left<16/T::static_size>( ranges_t{}, pattern_t{} )
                                  )
                ))
              , bitwise_cast<T>(bytes_t
                ( _mm_shuffle_epi8( bitwise_cast<bytes_t>(a1)
                                  , detail::mask_right<16/T::static_size>( ranges_t{}, pattern_t{} )
                                  )
                ))
              );
    }
  };
} } }

#endif
