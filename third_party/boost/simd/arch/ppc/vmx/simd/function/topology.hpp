//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/interleave.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/slide.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // VMX shuffling patterns
  struct  vmx_shuffle
        : default_matcher
        , slide_shuffle
        , interleave_shuffle
  {
    using default_matcher::process;
    using slide_shuffle::process;
    using interleave_shuffle::process;

    // Unary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, pattern_<Ps...> const& p)
    {
      return do_(a0, p, typename perform_zeroing<Ps...>::type{});
    }

    // Regular unary shuffling
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, pattern_<Ps...> const&, std::false_type const&)
    {
      using ranges_t  = brigand::range<int,0,16>;
      using pattern_t = brigand::integral_list<int,Ps...>;

      return  bitwise_cast<T>
              ( vec_perm( a0.storage(), a0.storage()
                        , detail::mask_all<16/T::static_size>(ranges_t{}, pattern_t{}).storage()
                        )
              );
    }

    // Masked unary shuffling - optimized by perming with 0 with minimal register usage
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T do_(const T & a0, pattern_<Ps...> const&, std::true_type const&)
    {
      using ranges_t  = brigand::range<int,0,16>;
      using pattern_t = brigand::integral_list<int,Ps...>;

      return  bitwise_cast<T>
              ( vec_perm( a0.storage(), vec_xor(a0.storage(),a0.storage())
                        , detail::mask_all<16,16/T::static_size>(ranges_t{}, pattern_t{}).storage()
                        )
              );
    }

    // Binary permutation handler
    template<typename T,int... Ps>
    static BOOST_FORCEINLINE T process(T const& a0, T const& a1, pattern_<Ps...> const& p)
    {
      return do_(a0, a1, p, typename perform_zeroing<Ps...>::type{});
    }

    // Masked binary shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<Ps...> const& p, std::true_type const&)
    {
      using s_t = typename T::value_type;
      return  do_(a0,a1,p,std::false_type{})
            & T( bitwise_cast<s_t>(zeroing_mask<std::uint32_t,Ps>::value)...);
    }

    // Regular binary shuffling
    template<typename T, int... Ps> static BOOST_FORCEINLINE
    T do_(const T& a0, const T & a1, pattern_<Ps...> const&, std::false_type const&)
    {
      using ranges_t  = brigand::range<int,0,16>;
      using pattern_t = brigand::integral_list<int,Ps...>;

      return  bitwise_cast<T>
              ( vec_perm( a0.storage(), a1.storage()
                        , detail::mask_all<16/T::static_size>(ranges_t{}, pattern_t{}).storage()
                        )
              );
    }
  };
} } }

#endif
