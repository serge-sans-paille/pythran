//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_PACK_TRAITS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_PACK_TRAITS_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/simd/arch/x86/sse2/pack_traits.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/pack_traits.hpp>

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-attributes"
#endif

namespace boost { namespace simd
{
  namespace detail
  {
    BOOST_SIMD_DEFINE_PACK_TRAITS(float         ,  8, __m256 );
    BOOST_SIMD_DEFINE_PACK_TRAITS(double        ,  4, __m256d);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int64_t  ,  4, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint64_t ,  4, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int32_t  ,  8, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint32_t ,  8, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int16_t  , 16, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint16_t , 16, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::int8_t   , 32, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(std::uint8_t  , 32, __m256i);
    BOOST_SIMD_DEFINE_PACK_TRAITS(char          , 32, __m256i);
  }

  namespace ext
  {
    template<typename Enable> struct abi_of<float,8,Enable>
    {
      using type = ::boost::simd::avx_;
    };

    template<typename Enable> struct abi_of<double,4,Enable>
    {
      using type = ::boost::simd::avx_;
    };

    template<typename T, std::size_t N>
    struct abi_of<  T, N
                  , typename std::enable_if<   std::is_integral<T>::value
                                            && (N*sizeof(T) == 32)
                                            >::type
                  >
    {
      using type = ::boost::simd::avx_;
    };
  }
} }

#if defined __GNUC__ && __GNUC__>=6
#pragma GCC diagnostic pop
#endif

#endif
