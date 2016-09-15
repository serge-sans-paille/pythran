//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPARE_NOT_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_COMPARE_NOT_EQUAL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/is_not_equal.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/any.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( compare_not_equal_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>, X>
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bool operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return do_(a0,a1, typename A0::storage_kind{});
    }

    BOOST_FORCEINLINE
    bool do_( const A0& a0, const A0& a1, aggregate_storage const&) const BOOST_NOEXCEPT
    {
      auto s0 = slice(a0);
      auto s1 = slice(a1);
      return compare_not_equal(s0[0], s1[0]) || compare_not_equal(s0[1], s1[1]);
    }

    template<typename K>
    BOOST_FORCEINLINE bool do_( const A0& a0, const A0& a1, K const&) const BOOST_NOEXCEPT
    {
      return bs::any(is_not_equal(a0,a1));
    }
  };
} } }

#endif
