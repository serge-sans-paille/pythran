//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_AS_SIMD_HPP_INCLUDED

#include <boost/simd/arch/x86/sse2/as_simd.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  namespace ext
  {
    template<typename T>
    struct as_simd<logical<T>, boost::simd::avx_> : as_simd<T, boost::simd::avx_> {};

    template<> struct as_simd<float, boost::simd::avx_>
    {
      using type = __m256;
    };

    template<> struct as_simd<double, boost::simd::avx_>
    {
      using type = __m256d;
    };

    template<typename T>
    struct as_simd< T, boost::simd::avx_
                  , typename std::enable_if<boost::dispatch::is_natural<T>::value>::type
                  >
    {
      using type = __m256i;
    };
  }
} }

#endif
