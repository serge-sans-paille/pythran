//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IS_SIMD_LOGICAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/all.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/constant/allbits.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD(is_simd_logical_
                         , (typename A0,typename X)
                         , bd::cpu_
                         , bs::pack_<bd::integer_<A0>,X>
                         )
  {
    BOOST_FORCEINLINE bool operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return bs::all(logical_or(is_equal(a0, Allbits<A0>()), is_eqz(a0)));
    }
  };

  BOOST_DISPATCH_OVERLOAD(is_simd_logical_
                         , (typename A0,typename X)
                         , bd::cpu_
                         , bs::pack_<bd::floating_<A0>,X>
                         )
  {
    BOOST_FORCEINLINE bool operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      using iA0 = bd::as_integer_t<A0, unsigned>;
      return is_simd_logical(bitwise_cast<iA0>(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD(is_simd_logical_
                         , (typename A0,typename X)
                         , bd::cpu_
                         , bs::pack_<bs::logical_<A0>,X>
                         )

  {
    BOOST_FORCEINLINE bool operator()(A0 const&) const
    {
      return true;
    }
  };
} } }

#endif

