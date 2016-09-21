//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_ALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Vec, typename Pointer)
                          , bs::avx_
                          , bs::pack_<bd::double_<Vec>, bs::avx_>
                          , bd::pointer_<bd::scalar_<bd::double_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1, Vec::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of double"
                      );
      _mm256_store_pd(a1,a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Vec, typename Pointer)
                          , bs::avx_
                          , bs::pack_<bd::single_<Vec>, bs::avx_>
                          , bd::pointer_<bd::scalar_<bd::single_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1, Vec::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of float"
                      );
      _mm256_store_ps(a1,a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( aligned_store_
                          , (typename Vec, typename Pointer)
                          , bs::avx_
                          , bs::pack_ < bd::integer_ < Vec>, bs::avx_>
                          , bd::pointer_<bd::scalar_<bd::integer_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator() (const Vec& a0, Pointer a1) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG( boost::simd::detail::is_aligned(a1, Vec::alignment)
                      , "boost::simd::aligned_load was performed on an unaligned pointer of integer"
                      );
       _mm256_store_si256(reinterpret_cast<__m256i*>(a1), a0);
    }
  };
} } }

#endif
