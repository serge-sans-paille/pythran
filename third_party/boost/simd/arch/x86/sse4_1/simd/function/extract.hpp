//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE4_1_SIMD_FUNCTION_EXTRACT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints8_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      enum { value = A1::value };
      return bd::scalar_of_t<A0>(_mm_extract_epi8(a0, value));
    }
  };

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints16_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      enum { value = A1::value };
      return bd::scalar_of_t<A0>(_mm_extract_epi16(a0, value));
    }
  };

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      enum { value = A1::value };
      return _mm_extract_epi32(a0, value);
    }
  };

#if !defined(BOOST_MSVC)
  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bd::ints64_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE bd::scalar_of_t<A0> operator()(A0 const & a0, A1 const &) const
    {
      enum { value = A1::value };
      return _mm_extract_epi64(a0, value);
    }
  };
#endif

  //------------------------------------------------------------------------------------------------
  BOOST_DISPATCH_OVERLOAD ( extract_
                          , (typename A0, typename A1)
                          , bs::sse4_1_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE float operator()(A0 const & a0, A1 const &) const
    {
      float f;
      enum { value = A1::value };
      _MM_EXTRACT_FLOAT(f, a0, value);
      return f;
    }
  };

} } }

#endif
