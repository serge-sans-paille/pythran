//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_SHUFFLE_HELPERS__HPP_INCLUDED
#define BOOST_SIMD_DETAIL_SHUFFLE_HELPERS__HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/forward.hpp>
#include <boost/simd/detail/brigand.hpp>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // Check if any -1 is in a pattern pack
  template<int... Ps>
  struct  perform_zeroing
        : brigand::bool_< !std::is_same < brigand::detail::bools_<true       , (Ps != -1)...>
                                        , brigand::detail::bools_<(Ps != -1)... , true      >
                                        >::value
                        >
  {};

  // -----------------------------------------------------------------------------------------------
  // Return a mask depending on a given pattern
  template<typename T, int P> struct zeroing_mask: std::integral_constant<T,P==-1 ? T(0) : ~(T(0))>
  {};

  // -----------------------------------------------------------------------------------------------
  // Find if a permutation is all on a0 or a1
  template<typename Perm> struct side;

  template<int... Is>
  struct side<pattern_<Is...>>
  {
    using idx_a0 = brigand::integral_list<bool,  (Is <  int(sizeof...(Is)))...              >;
    using idx_a1 = brigand::integral_list<bool, ((Is >= int(sizeof...(Is))) || (Is==-1))... >;

    using type = std::integral_constant < int
                                        , 0x01*brigand::all<idx_a0>::value
                                        + 0x02*brigand::all<idx_a1>::value
                                        >;
  };

  template<typename Perm> using side_t = typename side<Perm>::type;

  using a0_side   = std::integral_constant<int, 0x01>;
  using a1_side   = std::integral_constant<int, 0x02>;
  using zero_side = std::integral_constant<int, 0x03>;
  using both_side = std::integral_constant<int, 0x00>;

  // -----------------------------------------------------------------------------------------------
  // Slide a permutation by an offset
  template<int I, int Offset>
  struct remap : std::integral_constant<int,I==-1 ? -1 : I+Offset>
  {};

  // -----------------------------------------------------------------------------------------------
  // Computes a byte pattern from index pattern (optional fix value for zero-ing)
  template<int Bits, int I, typename Ps, std::uint8_t Fix = 0xFF> struct val
  {
    using P    = brigand::at_c<Ps,I/Bits>;
    using type = std::integral_constant < std::uint8_t
                                        , P::value == -1 ? Fix : (P::value*Bits + (I%Bits))
                                        >;
  };

  template<int SZ, typename... N, typename Ps>
  BOOST_FORCEINLINE
  pack<std::uint8_t,sizeof...(N)>
  mask_all(brigand::list<N...> const&, Ps const&)
  {
    return pack<std::uint8_t,sizeof...(N)>( val<SZ,N::value,Ps>::type::value... );
  }

  template<std::uint8_t Fix, int SZ, typename... N, typename Ps>
  BOOST_FORCEINLINE
  pack<std::uint8_t,sizeof...(N)>
  mask_all(brigand::list<N...> const&, Ps const&)
  {
    return pack<std::uint8_t,sizeof...(N)>( val<SZ,N::value,Ps,Fix>::type::value... );
  }

  // -----------------------------------------------------------------------------------------------
  // Computes a byte pattern from index pattern for binary shuffle - left side
  template<int Bits, int I, typename Ps> struct left_val
  {
    using sz   = brigand::size<Ps>;
    using P    = brigand::at_c<Ps,I/Bits>;
    using type = std::integral_constant < std::uint8_t
                                        , P::value==-1  ? 0xFF
                                                        : ( (P::value < sz::value)
                                                            ? (P::value*Bits + (I%Bits))
                                                            : 0xFF
                                                          )
                                        >;
  };

  template<int SZ, typename... N, typename Ps>
  BOOST_FORCEINLINE
  pack<std::uint8_t,sizeof...(N)> mask_left( brigand::list<N...> const&, Ps const& )
  {
    return pack<std::uint8_t,sizeof...(N)>( left_val<SZ,N::value,Ps>::type::value... );
  }

  // -----------------------------------------------------------------------------------------------
  // Computes a byte pattern from index pattern for binary shuffle - right side
  template<int Bits, int I, typename Ps> struct right_val
  {
    using sz    = std::integral_constant<int,brigand::size<Ps>::value>;
    using P     = brigand::at_c<Ps,I/Bits>;
    using type  = std::integral_constant < std::uint8_t
                                        , P::value==-1  ? 0xFF
                                                        : ( (P::value >= sz::value)
                                                            ? ((P::value-sz::value)*Bits + (I%Bits))
                                                            : 0xFF
                                                          )
                                        >;
  };

  template<int SZ, typename... N, typename Ps>
  BOOST_FORCEINLINE
  pack<std::uint8_t,sizeof...(N)> mask_right( brigand::list<N...> const&, Ps const& )
  {
    return pack<std::uint8_t,sizeof...(N)>( right_val<SZ,N::value,Ps>::type::value... );
  }
} } }

#endif
