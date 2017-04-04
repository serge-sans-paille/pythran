//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RSHL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_RSHL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shr.hpp>
#include <boost/simd/detail/nsm.hpp>

#ifndef NDEBUG
#include <boost/simd/function/max.hpp>
#include <boost/simd/constant/zero.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( rshl_
                            , (typename A0, typename A1, typename X)
                            , (nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bd::generic_<bd::integer_<A1>>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
    {
      #ifndef NDEBUG
      return if_else(is_gtz(a1), shift_left(a0, max(Zero<A1>(), a1)), shr(a0, max(Zero<A1>(), -a1)));
      #else
      return if_else(is_gtz(a1), shift_left(a0, a1), shr(a0, -a1));
      #endif
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( rshl_
                            , (typename A0, typename A1, typename X)
                            , (nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bd::generic_<bd::unsigned_<A1>>
                            )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const  A1&  a1) const BOOST_NOEXCEPT
    {
      return shift_left(a0, a1);
    }
  };
} } }

#endif
