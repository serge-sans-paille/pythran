//==================================================================================================
/*!
  @file

  Defines the as_simd metafunction for SSE2 like extensions

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_AS_SIMD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_AS_SIMD_HPP_INCLUDED

#include <boost/simd/arch/x86/sse1/as_simd.hpp>
#include <boost/simd/detail/dispatch/meta/is_natural.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  namespace ext
  {
    template<> struct as_simd<double, boost::simd::sse_>
    {
      using type = __m128d;
    };

    template<typename T>
    struct as_simd< T, boost::simd::sse_
                  , typename std::enable_if<boost::dispatch::is_natural<T>::value>::type
                  >
    {
      using type = __m128i;
    };
  }
} }

#endif
