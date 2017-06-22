//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPLEMENT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/logical_xor.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/constant/true.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bs = boost::simd;
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD_IF( complement_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bitwise_xor(bs::Allbits<A0>(), a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( complement_
                            , (typename A0,typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<A0>,X>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return logical_xor(bs::True<A0>(), a0);
    }
  };
} } }

#endif
