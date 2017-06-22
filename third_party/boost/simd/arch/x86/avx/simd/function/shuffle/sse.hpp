//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_SSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_SSE_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
 namespace bd = boost::dispatch;

 // ---------------------------------------------------------------------------------------------
  // AVX shuffling for SSE register
  struct  avx_128_shuffle : ssse3_shuffle
  {
    // -------------------------------------------------------------------------------------------
    // Reuse SSSE3 as back-up
    using ssse3_shuffle::process;

    // -------------------------------------------------------------------------------------------
    // Check if permutation its into mm_permute_p*
    template<int I0, int I1>
    struct permute2 : nsm::bool_<(I0!=-1) && (I1!=-1)> {};

    template<int I0, int I1, int I2, int I3>
    struct permute4 : nsm::bool_<(I0!=-1) && (I1!=-1) && (I2!=-1) && (I3!=-1)> {};

    // -------------------------------------------------------------------------------------------
    // Unary process for 2x64 registers
    template<typename T,int P0, int P1>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<P0,P1> const& p)
    {
      return do_(a0, p, typename permute2<P0,P1>::type{}, typename perform_zeroing<P0,P1>::type{});
    }

    template<typename T,int P0, int P1>
    static BOOST_FORCEINLINE T do_( T const& a0, pattern_<P0,P1> const&
                                  , tt::true_type const&, tt::false_type const&
                                  )
    {
      bd::as_floating_t<T> tmp =  _mm_permute_pd( bitwise_cast<bd::as_floating_t<T>>(a0)
                                                , (P0&1)|((P1&1)<<1)
                                                );
      return bitwise_cast<T>( tmp );
    }

    // -------------------------------------------------------------------------------------------
    // Unary process for 4x32 registers
    template<typename T,int P0, int P1, int P2, int P3>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<P0,P1,P2,P3> const& p)
    {
      return do_( a0, p
                , typename permute4<P0,P1,P2,P3>::type{}
                , typename perform_zeroing<P0,P1,P2,P3>::type{}
                );
    }

    template<typename T, int P0, int P1, int P2, int P3>
    static BOOST_FORCEINLINE T do_( T const& a0, pattern_<P0,P1,P2,P3> const&
                                  , tt::true_type const&, tt::false_type const&
                                  )
    {
      bd::as_floating_t<T> tmp = _mm_permute_ps( bitwise_cast<bd::as_floating_t<T>>(a0)
                                               , (P0&3)|((P1&3)<<2)|((P2&3)<<4)|((P3&3)<<6)
                                               );
      return bitwise_cast<T>( tmp );
    }

    // -------------------------------------------------------------------------------------------
    // Common case when everything crumbles
    template<typename T, int... Ps, typename PR, typename PZ>
    static BOOST_FORCEINLINE T do_( T const& a0, pattern_<Ps...> const& p
                                  , PR const&, PZ const&
                                  )
    {
      return ssse3_shuffle::process(a0,p);
    }
  };
} } }

#endif
