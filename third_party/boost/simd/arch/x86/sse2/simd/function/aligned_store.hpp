//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/simd/detail/is_aligned.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Vec, typename Pointer)
                          , bs::sse2_
                          , bs::pack_ < bd::double_ < Vec>, bs::sse_>
                          , bd::pointer_<bd::scalar_<bd::double_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1, Vec::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of integer"
                      );
      _mm_store_pd((double*)(a1),a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( aligned_store_
                            , (typename Vec, typename Pointer)
                            , (bs::is_pointing_to<Pointer,typename Vec::value_type>)
                            , bs::sse2_
                            , bs::pack_ < bd::integer_ < Vec>, bs::sse_>
                            , bd::pointer_<bd::scalar_<bd::integer_<Pointer>>,1u>
                            )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1, Vec::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of integer"
                      );
       _mm_store_si128((__m128i*)(a1), a0);
    }
  };
} } }

#endif
