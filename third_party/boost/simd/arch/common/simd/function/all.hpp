//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ALL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/hmsb.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/splatted.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( all_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>, X>
                          )
  {
    BOOST_FORCEINLINE bool do_(const A0& a0, aggregate_storage const&) const BOOST_NOEXCEPT
    {
      auto const all0 = all(slice_high(a0));
      auto const all1 = all(slice_low(a0) );
      return  all0 && all1;
    }

    template<typename K>
    BOOST_FORCEINLINE bool do_(const A0& a0, K const&) const BOOST_NOEXCEPT
    {
      return hmsb(genmask(a0)).all();
    }

    BOOST_FORCEINLINE bool operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return do_(a0, typename A0::storage_kind{});
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( all_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::splatted_tag
                            , bs::pack_<bd::fundamental_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE as_logical_t<A0>
    operator()(bs::splatted_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return as_logical_t<A0>(all(a0));
    }
  };
} } }

#endif
