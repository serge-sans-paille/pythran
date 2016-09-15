//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/split.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( split_multiplies_
                            , (typename A0, typename X)
                            , (bd::is_upgradable<A0>)
                            , bd::cpu_
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            , bs::pack_<bd::arithmetic_<A0>, X>
                            )
  {
    using result_t = std::pair<bd::upgrade_t<A0>,bd::upgrade_t<A0>>;

    BOOST_FORCEINLINE result_t operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      auto s0 = split(a0);
      auto s1 = split(a1);

      return { s0[0]*s1[0], s0[1]*s1[1] };
    }
  };
} } }

#endif
