//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ONE_ELSE_ZERO_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ONE_ELSE_ZERO_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/if_else_zero.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( if_one_else_zero_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return bs::if_else_zero(a0, A0(1));
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( if_one_else_zero_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>, X>
                            )
  {
    using result = bs::as_arithmetic_t<A0>;
    BOOST_FORCEINLINE result operator()( const A0& a0) const BOOST_NOEXCEPT
    {
      return bs::if_else_zero(a0, result(1));
    }
  };
} } }

#endif

