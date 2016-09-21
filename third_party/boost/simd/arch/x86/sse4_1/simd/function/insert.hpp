//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_INSERT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_INSERT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( insert_
                          , (typename A0, typename A1, typename A2)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints8_<A0>,bs::sse_>
                          , bd::constant_< bd::integer_<A1>>
                          , bd::scalar_< bd::unspecified_<A2>>
                          )
  {

    BOOST_FORCEINLINE void operator() (  A0 & a0, A1 const &, A2 const & a2) const BOOST_NOEXCEPT
    {
      enum { value = A1::value };
      a0 = _mm_insert_epi8(a0, a2, value);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( insert_
                          , (typename A0, typename A1, typename A2)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints32_<A0>,bs::sse_>
                          , bd::constant_< bd::integer_<A1>>
                          , bd::scalar_< bd::unspecified_<A2>>
                          )
  {

    BOOST_FORCEINLINE void operator() (  A0 & a0, A1 const &, A2 const & a2) const BOOST_NOEXCEPT
    {
      enum { value = A1::value };
      a0 = _mm_insert_epi32(a0, a2, value);
    }
  };

#if !defined(BOOST_MSVC)
  BOOST_DISPATCH_OVERLOAD ( insert_
                          , (typename A0, typename A1, typename A2)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints64_<A0>,bs::sse_>
                          , bd::constant_< bd::integer_<A1>>
                          , bd::scalar_< bd::unspecified_<A2>>
                          )
  {

    BOOST_FORCEINLINE void operator() (  A0 & a0, A1 const &, A2 const & a2) const BOOST_NOEXCEPT
    {
      enum { value = A1::value };
      a0 = _mm_insert_epi64(a0, a2, value);
    }
  };
#endif

} } }

#endif
