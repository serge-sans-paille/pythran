//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IFNOT_MINUS_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IFNOT_MINUS_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/if_zero_else.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( ifnot_minus_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::fundamental_<A0>, X>
                            , bs::pack_<bd::unspecified_<A1>, X>
                            , bs::pack_<bd::unspecified_<A1>, X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1, A1 const& a2) const BOOST_NOEXCEPT
    {
      return a1-if_zero_else(a0, a2);
    }
  };
} } }

#endif

