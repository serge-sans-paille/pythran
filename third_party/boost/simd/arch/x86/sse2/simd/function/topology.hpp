//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/arch/x86/sse1/simd/function/topology.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // Local masking utility
  template<int P0,int P1>
  struct mask_pd : tt::integral_constant<int, _MM_SHUFFLE2(P1&1,P0&1)>
  {};

  // -----------------------------------------------------------------------------------------------
  // SSE cardinal 2 specialisation
  template<int P0, int P1> struct sse_topology<2,P0,P1>
  {
    // is the pattern leads to a direct shuffle call?
    static const bool direct   = (P0 <= 1) && (P1 >= 2 || P1 == -1);
    using type = typename std::conditional< direct
                                          , direct_<P0,P1>
                                          , indirect_<P0,P1>
                                          >::type;
  };

  // -----------------------------------------------------------------------------------------------
  // SSE2 shuffling patterns
  struct  sse2_shuffle
        : sse1_shuffle
  {
    using sse1_shuffle::process;

    // Unary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<Ps...> const& p)
    {
      return do_(a0, p, typename perform_zeroing<Ps...>::type{});
    }

    // Regular unary shuffling - ints32
    template<typename T,int P0,int P1,int P2,int P3> static BOOST_FORCEINLINE
    T do_(const T& a0, pattern_<P0,P1,P2,P3> const&, tt::false_type const&)
    {
      return _mm_shuffle_epi32(a0, (mask_ps<P0,P1,P2,P3>::value));
    }

    // Regular unary shuffling -  type64
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, pattern_<P0,P1> const&, tt::false_type const&)
    {
      using f_t = bd::as_floating_t<T>;
      auto const v = bitwise_cast<f_t>(a0);
      return bitwise_cast<T>( f_t(_mm_shuffle_pd(v, v, (detail::mask_pd<P0,P1>::value))) );
    }

    // Masked unary shuffling
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T do_(const T & a0, pattern_<Ps...> const& p, tt::true_type const&)
    {
      using s_t = typename T::value_type;
      using i_t = bd::as_integer_t<s_t,unsigned>;
      return  do_(a0,p,tt::false_type{})
            & T ( bitwise_cast<s_t>(zeroing_mask<i_t,Ps>::value)... );
    }

    // Binary permutation handler - ints32
    template<typename T,int P0,int P1,int P2,int P3>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<P0,P1,P2,P3> const&)
    {
      return bitwise_cast<T>( shuffle<P0,P1,P2,P3>( bitwise_cast<bd::as_floating_t<T>>(a0)
                                                  , bitwise_cast<bd::as_floating_t<T>>(a1)
                                                  )
                            );
    }

    // Binary permutation handler - type64
    template<typename T,int P0,int P1>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<P0,P1> const& p)
    {
      return do_(a0, a1, p, typename perform_zeroing<P0,P1>::type{});
    }

    // Masked binary shuffling
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<P0,P1> const& p, tt::true_type const&)
    {
      using s_t = typename T::value_type;
      return  do_(a0,a1,p,tt::false_type{})
            & T ( bitwise_cast<s_t>(zeroing_mask<std::uint64_t,P0>::value)
                , bitwise_cast<s_t>(zeroing_mask<std::uint64_t,P1>::value)
                );
    }

    // Regular binary shuffling
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<P0,P1> const&, tt::false_type const&)
    {
      return do_(a0, a1, typename sse_topology<2,P0,P1>::type{});
    }

    // Mixed shuffling
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, pattern_<P0,P1> const& p)
    {
      return default_matcher::process(a0,a1,p);
    }

    // Direct shuffling
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, direct_<P0,P1> const&)
    {
      using f_t = bd::as_floating_t<T>;
      auto const v0 = bitwise_cast<f_t>(a0);
      auto const v1 = bitwise_cast<f_t>(a1);
      return bitwise_cast<T>(f_t(_mm_shuffle_pd(v0, v1, (detail::mask_pd<P0,P1>::value))));
    }

    // Indirect shuffling is direct shuffling with a0/a1 permuted
    template<typename T,int P0,int P1> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, indirect_<P0,P1> const&)
    {
      return do_(a1,a0,detail::direct_<P0,P1>{});
    }
  };
} } }

#endif
