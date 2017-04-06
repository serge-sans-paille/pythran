//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/adapted/std/integral_constant.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;
  namespace tt = nsm::type_traits;

  template<typename A0, typename A1>
  struct bc_helper
  {
    using select_t  = nsm::bool_<(A1::value >= 0 && A1::value < A0::static_size)>;
    using sel_t     = tt::integral_constant<int, (A1::value >= A0::static_size/2) ? 1 : 0>;
    using idx_t     = tt::integral_constant<int, A1::value - sel_t::value*(A0::static_size/2)>;
    using type      = typename A0::template resize<A0::static_size/2>;
  };

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::single_<A0>,bs::avx_>
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

      h_t half =  _mm256_extractf128_ps(a0, sel_t::value);
      return      _mm256_broadcast_ps(&broadcast<idx_t::value>(half).storage());
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<bd::double_<A0>,bs::avx_>
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

      h_t half =  _mm256_extractf128_pd(a0, sel_t::value);
      return      _mm256_broadcast_pd(&broadcast<idx_t::value>(half).storage());
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::avx_
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
      auto bc = broadcast<idx_t::value>(half);
      return combine(bc,bc);
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };
} } }

#endif
