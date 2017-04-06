//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/combine.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  //  int16->float
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int16_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::single_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      auto x = boost::simd::slice(a0);
      return boost::simd::combine( boost::simd::pack_cast<typename A1::type>(x[0])
                                 , boost::simd::pack_cast<typename A1::type>(x[1])
                                 );
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int16->int32
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int16_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi16_epi32(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int16_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi16_epi32(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int32->int64
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int64_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi32_epi64(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int32_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint64_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi32_epi64(a0);
    }
  };


  //------------------------------------------------------------------------------------------------
  //  int8->float
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int8_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::single_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      auto x = boost::simd::slice(a0);
      return boost::simd::combine( boost::simd::pack_cast<typename A1::type>(x[0])
                                 , boost::simd::pack_cast<typename A1::type>(x[1])
                                 );
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int8->int16
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int8_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int16_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi8_epi16(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::int8_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint16_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi8_epi16(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  uint16->int32
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu16_epi32(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint16_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu16_epi32(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  uint32->int64
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int64_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu32_epi64(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint32_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint64_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu32_epi64(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  uint8->int16
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint8_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::int16_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu8_epi16(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::uint8_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::uint16_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepu8_epi16(a0);
    }
  };
} } }

#endif
