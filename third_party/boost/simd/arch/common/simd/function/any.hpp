//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ANY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ANY_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/hmsb.hpp>
#include <boost/simd/function/splatted.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( any_
                            , (typename A0, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::fundamental_<A0>, X>
                            )
  {
    BOOST_FORCEINLINE bool do_(const A0& a0, aggregate_storage const&) const BOOST_NOEXCEPT
    {
      return any(slice_high(a0)) || any(slice_low(a0));
    }

    template<typename K>
    BOOST_FORCEINLINE bool do_(const A0& a0, K const&) const BOOST_NOEXCEPT
    {
      return hmsb(genmask(a0)).any();
    }

    BOOST_FORCEINLINE bool operator()(const A0& a0) const BOOST_NOEXCEPT
    {
      return do_(a0, typename A0::storage_kind{});
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( any_
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
      return as_logical_t<A0>(any(a0));
    }
  };
} } }

#endif
