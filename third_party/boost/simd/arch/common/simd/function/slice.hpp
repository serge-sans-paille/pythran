//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLICE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLICE_HPP_INCLUDED

#include <boost/simd/function/slice_high.hpp>
#include <boost/simd/function/slice_low.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD( slice_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    using base_t   = typename T::template resize<T::static_size/2>;
    using result_t = std::array<base_t,2>;

    template<typename... N>
    static BOOST_FORCEINLINE result_t do_ ( T const& a, aggregate_storage const&) BOOST_NOEXCEPT
    {
      return a.storage();
    }

    template<typename K>
    static BOOST_FORCEINLINE result_t do_( T const& a, K const&) BOOST_NOEXCEPT
    {
      return result_t{{ slice_low(a), slice_high(a) }};
    }

    BOOST_FORCEINLINE result_t operator()(T const& a) const BOOST_NOEXCEPT
    {
      return do_( a, typename base_t::traits::storage_kind{} );
    }
  };
} } }

#endif
