//==================================================================================================
/*!
  @file

  Defines SSE2 functions for SIMD storage used by pack

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_PACK_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_PACK_TRAITS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/arch/x86/sse1/pack_traits.hpp>
#include <boost/simd/detail/pack_traits.hpp>
#include <boost/simd/detail/nsm.hpp>

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace boost { namespace simd
{
  namespace detail
  {
    BOOST_SIMD_DEFINE_PACK_TRAITS(double        ,  2, __m128d);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int64_t  ,  2, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint64_t ,  2, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int32_t  ,  4, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint32_t ,  4, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int16_t  ,  8, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint16_t ,  8, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int8_t   , 16, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint8_t  , 16, __m128i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(char          , 16, __m128i);
  }

  namespace ext
  {
    template<typename Enable> struct abi_of<double,2,Enable>
    {
      using type = ::boost::simd::sse_;
    };

    template<typename T, std::size_t N>
    struct abi_of<  T, N
                  , typename std::enable_if<   std::is_integral<T>::value
                                            && (N*sizeof(T) == 16)
                                            >::type
                  >
    {
      using type = ::boost::simd::sse_;
    };
  }
} }

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic pop
#endif

#endif
