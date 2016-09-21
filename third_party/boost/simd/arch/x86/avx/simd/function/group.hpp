//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( group_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>, avx_>
                          , bs::pack_<bd::double_<A0>, avx_>
                          )
   {
      using result = bd::downgrade_t<A0>;

      BOOST_FORCEINLINE result operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        using slice_t = typename A0::template rebind<typename result::value_type>;
        return combine(slice_t(_mm256_cvtpd_ps(a0)),slice_t(_mm256_cvtpd_ps(a1)));
      }
   };

   BOOST_DISPATCH_OVERLOAD( group_
                          , (typename A0)
                          , bs::avx_
                          , bs::pack_<bd::integer_<A0>, avx_>
                          , bs::pack_<bd::integer_<A0>, avx_>
                          )
   {
      using result = bd::downgrade_t<A0>;

      BOOST_FORCEINLINE result operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        auto a0x = slice(a0), a1x = slice(a1);
        auto v0  = group(a0x[0], a0x[1]);
        auto v1  = group(a1x[0], a1x[1]);

        return _mm256_insertf128_si256(_mm256_castsi128_si256(v0), v1, 1);
      }
   };

   BOOST_DISPATCH_OVERLOAD( group_
                          , (typename A0)
                          , bs::avx_
                          , bs::saturated_tag
                          , bs::pack_<bd::integer_<A0>, avx_>
                          , bs::pack_<bd::integer_<A0>, avx_>
                          )
   {
      using result = bd::downgrade_t<A0>;

      BOOST_FORCEINLINE
      result operator()(bs::saturated_tag const&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        auto a0x = slice(a0), a1x = slice(a1);
        auto v0  = saturated_(group)(a0x[0], a0x[1]);
        auto v1  = saturated_(group)(a1x[0], a1x[1]);

        return _mm256_insertf128_si256(_mm256_castsi128_si256(v0), v1, 1);
      }
   };
} } }

#endif
