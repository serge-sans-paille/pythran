//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_AS_SIMD_HPP_INCLUDED

#include <boost/simd/arch/common/simd/as_simd.hpp>
#include <boost/simd/arch/x86/tags.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  namespace ext
  {
    template<> struct as_simd<float, boost::simd::sse_>
    {
      using type = __m128;
    };

    template<typename T>
    struct  as_simd<logical<T>, boost::simd::sse_>
          : as_simd<T, boost::simd::sse_> {};
  }
} }

#endif
