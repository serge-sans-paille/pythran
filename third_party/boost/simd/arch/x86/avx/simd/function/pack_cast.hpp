//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_PACK_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  //  float->int32
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::int32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvttps_epi32(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  float->double
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::double_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtps_pd(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int32->float
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::int32_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::single_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi32_ps(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  int32->double
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::int32_<A0>,bs::sse_>
                          , bd::target_<bd::scalar_<bd::double_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtepi32_pd(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  double->int32
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::int32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvttpd_epi32(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::uint32_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvttpd_epi32(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  //  double->float
  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>,bs::avx_>
                          , bd::target_<bd::scalar_<bd::single_<A1>>>
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return _mm256_cvtpd_ps(a0);
    }
  };
} } }

#endif
