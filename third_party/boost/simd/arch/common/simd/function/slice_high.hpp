//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED

#include <boost/simd/function/extract.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;


  BOOST_DISPATCH_OVERLOAD ( slice_high_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    static const std::size_t half = T::static_size/2;
    using result_t   = typename T::template resize<half>;

    template<typename... N>
    static BOOST_FORCEINLINE
    result_t do_ ( T const& a, aggregate_storage const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return a.storage()[1];
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE
    result_t do_( T const& a, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return  result_t(bs::extract<N::value>(a)... );
    }

    BOOST_FORCEINLINE result_t operator()(T const& a) const BOOST_NOEXCEPT
    {
      return do_( a, typename T::traits::storage_kind{}
                , nsm::range<std::size_t, half, T::static_size>{}
                );
    }
  };
} } }

#endif
