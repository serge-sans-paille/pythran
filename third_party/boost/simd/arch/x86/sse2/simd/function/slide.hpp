//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SLIDE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SLIDE_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  namespace tt = nsm::type_traits;

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::sse2_
                          , bs::pack_< bd::fundamental_<T>, bs::sse_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    using bits_t  = typename T::template rebind<std::uint8_t>::template resize<16>;
    using bcnt    = tt::integral_constant<std::size_t,16u/T::static_size>;

    // slide with positive offset
    static BOOST_FORCEINLINE T side(T const& a0, tt::true_type const&) BOOST_NOEXCEPT
    {
      using imm = tt::integral_constant<std::size_t,Offset::value*bcnt::value>;
      bits_t tmp = _mm_srli_si128(bitwise_cast<bits_t>(a0),imm::value);
      return bitwise_cast<T>(tmp);
    }

    // slide with negative offset
    static BOOST_FORCEINLINE T side( T const& a0, tt::false_type const& ) BOOST_NOEXCEPT
    {
      using imm = tt::integral_constant<std::size_t,(-Offset::value)*bcnt::value>;
      bits_t tmp = _mm_slli_si128(bitwise_cast<bits_t>(a0),imm::value);
      return bitwise_cast<T>(tmp);
    }

    BOOST_FORCEINLINE T operator()(T const& a0, Offset const&) const BOOST_NOEXCEPT
    {
      return side(a0, nsm::bool_<(Offset::value >= 0)>{});
    }
  };

  BOOST_DISPATCH_OVERLOAD ( slide_
                          , (typename T, typename Offset)
                          , bs::sse2_
                          , bs::pack_< bd::fundamental_<T>, bs::sse_ >
                          , bs::pack_< bd::fundamental_<T>, bs::sse_ >
                          , bd::constant_<bd::integer_<Offset>>
                          )
  {
    using bits_t  = typename T::template rebind<std::uint8_t>::template resize<16>;

    BOOST_FORCEINLINE T operator()(T const& a0, T const& a1, Offset const&) const BOOST_NOEXCEPT
    {
      // Compute relative offsets for shifted loads pair
      using bcnt  = tt::integral_constant<std::size_t,(16u/T::static_size)>;
      using ls    = tt::integral_constant<std::size_t,bcnt::value*Offset::value>;
      using rs    = tt::integral_constant<std::size_t,bcnt::value*(T::static_size-Offset::value)>;

      // Shift everything in place
      return bitwise_cast<T>(bits_t( _mm_or_si128( _mm_srli_si128(bitwise_cast<bits_t>(a0),ls::value)
                                                 , _mm_slli_si128(bitwise_cast<bits_t>(a1),rs::value))
                                          )
                            );
    }
  };
} } }

#endif
