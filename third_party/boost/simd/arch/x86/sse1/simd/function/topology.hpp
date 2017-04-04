//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/deinterleave.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/interleave.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/repeat.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/slide.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace detail
{
  namespace tt = nsm::type_traits;
  // -----------------------------------------------------------------------------------------------
  // Local masking utility
  template<int P0,int P1, int P2, int P3>
  struct mask_ps : tt::integral_constant<int, _MM_SHUFFLE(P3&3,P2&3,P1&3,P0&3)>
  {};

  // -----------------------------------------------------------------------------------------------
  // Markup for SSE topology
  // direct_    means the pattern is of the shape { a0 | a1 }
  // indirect_  means the pattern is of the shape { a1 | a0 }
  template<int... Ps> struct direct_    {};
  template<int... Ps> struct indirect_  {};

  // -----------------------------------------------------------------------------------------------
  // Check if a permutation follows SSE shuffle restriction in a way or another
  template<int Card, int... Ps> struct sse_topology;

  // -----------------------------------------------------------------------------------------------
  // SSE handle only cardinal 4 through float
  template<int P0, int P1, int P2, int P3> struct sse_topology<4,P0,P1,P2,P3>
  {
    static const bool direct   = (P0 < 4) && (P1 < 4)
                              && (P2 >= 4 || P2 == -1)
                              && (P3 >= 4 || P3 == -1);

    static const bool indirect = (P2 < 4) && (P3 < 4)
                              && (P0 >= 4 || P0 == -1)
                              && (P1 >= 4 || P1 == -1);

    // is the pattern lead to a direct or indirect shuffling ?
    using type = typename std::conditional< direct
                                          , direct_<P0,P1,P2,P3>
                                          , typename std::conditional < indirect
                                                                      , indirect_<P0,P1,P2,P3>
                                                                      , pattern_<P0,P1,P2,P3>
                                                                      >::type
                                          >::type;
  };

  // -----------------------------------------------------------------------------------------------
  // Specific SSE1 shuffle patterns avoiding _mm_shuffle_ps
  struct sse1_specific_shuffle
  {
    // Specialized Binary permutation handler
    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<0,1,4,5> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movelh_ps(bitwise_cast<f_t>(a0),bitwise_cast<f_t>(a1));
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<4,5,0,1> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movelh_ps(bitwise_cast<f_t>(a1),bitwise_cast<f_t>(a0));
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<2,3,6,7> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movehl_ps(bitwise_cast<f_t>(a1),bitwise_cast<f_t>(a0));
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<6,7,2,3> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movehl_ps(bitwise_cast<f_t>(a0),bitwise_cast<f_t>(a1));
      return bitwise_cast<T>(tmp);
    }

    // Specialized Unary permutation handler
    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<0,1,-1,-1> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movelh_ps(bitwise_cast<f_t>(a0),Zero<f_t>());
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<-1,-1,0,1> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movelh_ps(Zero<f_t>(),bitwise_cast<f_t>(a0));
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<-1,-1,2,3> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movehl_ps(bitwise_cast<f_t>(a0),Zero<f_t>());
      return bitwise_cast<T>(tmp);
    }

    template<typename T>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<2,3,-1,-1> const&)
    {
      using f_t = boost::dispatch::as_floating_t<T>;
      f_t tmp = _mm_movehl_ps(Zero<f_t>(),bitwise_cast<f_t>(a0));
      return bitwise_cast<T>(tmp);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // SSE1 shuffling patterns
  struct  sse1_shuffle
        : default_matcher
        , repeat_shuffle
        , slide_shuffle
        , deinterleave_shuffle
        , interleave_shuffle
        , sse1_specific_shuffle
  {
    using default_matcher::process;
    using repeat_shuffle::process;
    using slide_shuffle::process;
    using deinterleave_shuffle::process;
    using interleave_shuffle::process;
    using sse1_specific_shuffle::process;

    // Unary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<Ps...> const& p)
    {
      return do_(a0, p, typename perform_zeroing<Ps...>::type{});
    }

    // Regular unary shuffling
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, pattern_<Ps...> const&, tt::false_type const&)
    {
      return _mm_shuffle_ps(a0,a0, mask_ps<Ps...>::value);
    }

    // Masked unary shuffling
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T do_(const T & a0, pattern_<Ps...> const& p, tt::true_type const&)
    {
      using s_t = typename T::value_type;
      return  do_(a0,p,tt::false_type{})
            & T( bitwise_cast<s_t>(zeroing_mask<std::uint32_t,Ps>::value)...);
    }

    // Binary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<Ps...> const& p)
    {
      return do_(a0, a1, p, typename perform_zeroing<Ps...>::type{});
    }

    // Masked binary shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<Ps...> const& p, tt::true_type const&)
    {
      using s_t = typename T::value_type;
      return  do_(a0,a1,p,tt::false_type{})
            & T( bitwise_cast<s_t>(zeroing_mask<std::uint32_t,Ps>::value)...);
    }

    // Regular binary shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<Ps...> const&, tt::false_type const&)
    {
      return do_(a0, a1, typename sse_topology<4,Ps...>::type{});
    }

    // Mixed shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, pattern_<Ps...> const& p)
    {
      return default_matcher::process(a0,a1,p);
    }

    // Direct shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, direct_<Ps...> const&)
    {
      return _mm_shuffle_ps(a0, a1, mask_ps<Ps...>::value);
    }

    // Indirect shuffling is direct shuffling with a0/a1 permuted
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T& a1, indirect_<Ps...> const&)
    {
      return _mm_shuffle_ps(a1, a0, mask_ps<Ps...>::value);
    }
  };
} } }

#endif
