//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_BITWISE_SELECT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_andnot.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( bitwise_select_
                            , (typename A0, typename A1, typename X, typename Y)
                            , (nsm::bool_<A0::static_size==A1::static_size>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X >
                            , bs::pack_<bd::arithmetic_<A1>, Y >
                            , bs::pack_<bd::arithmetic_<A1>, Y >
                            )
  {
    BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1, A1 const& a2) const BOOST_NOEXCEPT
    {
      return bitwise_or(bitwise_and(a1, a0), bitwise_andnot(a2,a0));
    }
  };
} } }

#endif
