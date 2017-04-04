//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::avx2_
                          , bs::pack_<bd::integer_<A0>,bs::avx_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return do_(a0,typename bc_helper<A0,A1>::select_t{});
    }

    static BOOST_FORCEINLINE A0 do_(A0 const& a0, nsm::bool_<true> const&) BOOST_NOEXCEPT
    {
      using sel_t = typename bc_helper<A0,A1>::sel_t;
      using idx_t = typename bc_helper<A0,A1>::idx_t;
      using h_t   = typename bc_helper<A0,A1>::type;

      h_t half =  _mm256_extractf128_si256(a0, sel_t::value);
      return      _mm256_broadcastsi128_si256(broadcast<idx_t::value>(half));
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };
} } }

#endif
