//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_INC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_INC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_plus.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( if_inc_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>, X>
                            , bs::pack_<bd::integer_<A1>, X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()(const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      return do_(a0,a1,is_bitwise_logical_t<A0>{});
    }

    BOOST_FORCEINLINE A1 do_(const A0& a0, const A1& a1, tt::true_type const&) const BOOST_NOEXCEPT
    {
      return a1 - bitwise_cast<A1>(genmask(a0));
    }

    BOOST_FORCEINLINE A1 do_(const A0& a0, const A1& a1, tt::false_type const&) const BOOST_NOEXCEPT
    {
      return if_plus(a0, a1, One<A1>());
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( if_inc_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A1>, X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
    {
      return if_plus(a0, a1, One<A1>());
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( if_inc_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A1>, X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
    {
      return if_plus(a0, a1, One<A1>());
    }
  };
} } }

#endif
