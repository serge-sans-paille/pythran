//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_PERM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_PERM_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  // -----------------------------------------------------------------------------------------------
  // Shuffle using blend patterns hierarchy
  template<typename Index, typename P> struct permute_pattern : P
  {
    using parent = P;
  };

  namespace detail
  {
    // ---------------------------------------------------------------------------------------------
    // Check if a permutation can use blend_p*
    template<int... Ps> struct is_permute
    {
      using sz = tt::integral_constant<int,sizeof...(Ps)/2>;
      using l0 = nsm::range<int,0           ,   sz::value>;
      using h0 = nsm::range<int,sz::value   , 2*sz::value>;
      using l1 = nsm::range<int,2*sz::value , 3*sz::value>;
      using h1 = nsm::range<int,3*sz::value , 4*sz::value>;

      template<typename F, typename S, int Mask>
      using i_t = nsm::pair< nsm::append<F,S>, tt::integral_constant<int,Mask> >;

      using lst = nsm::map< i_t<h0,l0,0x01>, i_t<l1,l0,0x02>, i_t<h1,l0,0x03>, i_t<h1,h0,0x13>
                              , i_t<l0,l1,0x20>, i_t<h0,l1,0x21>, i_t<h1,l1,0x23>, i_t<h0,h1,0x31>
                              >;

      using mode = nsm::at<lst, nsm::integral_list<int,Ps...>>;
      using type = nsm::bool_<!std::is_same<mode, nsm::no_such_type_>::value>;
    };

    template<int P0>         struct is_permute<P0>    : tt::false_type {};
    template<int P0, int P1> struct is_permute<P0,P1> : tt::false_type {};

    // ---------------------------------------------------------------------------------------------
    // AVX permute patterns
    struct perm_shuffle
    {
      template<typename T, typename Mask, typename P>
      static BOOST_FORCEINLINE T process(T const& a0, permute_pattern<Mask,P> const&)
      {
        return perm2_<T>( a0.storage(), a0.storage(), Mask{} );
      }

      template<typename T, typename Mask, typename P>
      static BOOST_FORCEINLINE T process(T const& a0, T const& a1, permute_pattern<Mask,P> const&)
      {
        return perm2_<T>( a0.storage(), a1.storage(), Mask{} );
      }

      template<typename T, typename Mask>
      static BOOST_FORCEINLINE T perm2_( __m256d const& a0, __m256d const& a1, Mask const&)
      {
        return _mm256_permute2f128_pd(a0, a1, Mask::value);
      }

      template<typename T, typename Mask>
      static BOOST_FORCEINLINE T perm2_ ( __m256 const& a0, __m256 const& a1, Mask const&)
      {
        return _mm256_permute2f128_ps(a0, a1, Mask::value);
      }

      template<typename T, typename Mask>
      static BOOST_FORCEINLINE T perm2_ ( __m256i const& a0, __m256i const& a1, Mask const&)
      {
        return _mm256_permute2f128_si256(a0, a1, Mask::value);
      }
    };
  }
} }

// -------------------------------------------------------------------------------------------------
// Hierarchize permute patterns
namespace boost { namespace dispatch { namespace ext
{
  template<int... Ps,typename Origin>
  struct pattern_hierarchy< boost::simd::detail::pattern_<Ps...>,Origin
                          , typename std::enable_if<simd::detail::is_permute<Ps...>::type::value>::type
                          >
  {
    using type = simd::permute_pattern< typename simd::detail::is_permute<Ps...>::mode
                                      , simd::detail::pattern_<Ps...>
                                      >;
  };
} } }

#endif
