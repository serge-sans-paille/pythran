//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/split_high.hpp>
#include <boost/simd/function/split_low.hpp>
#include <array>


namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( split_
                            , (typename A0, typename X)
                            , (bd::is_upgradable<A0>)
                            , bd::cpu_
                            , bs::pack_<bd::unspecified_<A0>, X>
                            )
  {
    using result_t = std::array<bd::upgrade_t<A0>,2>;

    BOOST_FORCEINLINE result_t operator()(A0 const& a) const BOOST_NOEXCEPT
    {
      return {{ split_low(a), split_high(a)}};
    }
  };
} } }

#endif
