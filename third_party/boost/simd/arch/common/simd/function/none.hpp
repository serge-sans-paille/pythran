//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NONE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NONE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/splatted.hpp>
#include <boost/simd/function/hmsb.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( none_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bool do_(const A0& a0, aggregate_storage const&) const BOOST_NOEXCEPT
    {
      auto const all0 = none(slice_high(a0));
      auto const all1 = none(slice_low(a0) );
      return  all0 && all1;
    }

    template<typename K>
    BOOST_FORCEINLINE bool do_(const A0& a0, K const&) const BOOST_NOEXCEPT
    {
      return hmsb(genmask(a0)).none();
    }

    BOOST_FORCEINLINE bool operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return do_(a0, typename A0::storage_kind{});
    }
  };

  BOOST_DISPATCH_OVERLOAD ( none_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::splatted_tag
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE
    as_logical_t<A0> operator()( bs::splatted_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return as_logical_t<A0>(bs::none(a0));
    }
  };
} } }

#endif
