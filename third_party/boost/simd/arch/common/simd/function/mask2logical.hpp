//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MASK2LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_MASK2LOGICAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/assert_utils.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF (  mask2logical_
                             , (typename A0,typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_<bd::arithmetic_<A0>,X>
                             )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      BOOST_ASSERT_MSG(assert_is_mask(a0), "Argument to mask2logical is not a valid logical mask");
      return bitwise_cast<bs::as_logical_t<A0>>(a0);
    }
  };
} } }

#endif
