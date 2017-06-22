//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_RANDOM_ACCESS_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_RANDOM_ACCESS_ITERATOR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/adapted/std/iterator.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load from a random access range
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Begin, typename End, typename Ext)
                          , bd::cpu_
                          , bd::random_access_iterator_<bd::scalar_<bd::unspecified_<Begin>>>
                          , bd::random_access_iterator_<bd::scalar_<bd::unspecified_<End>>>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    // Aggregate case: fill in the storage by calling load twice
    template<typename... N> static BOOST_FORCEINLINE
    target_t do_(Begin const& b, aggregate_storage const&, nsm::list<N...> const&)
    {
      Begin   b1 = b  + target_t::traits::element_size
            , b2 = b1 + target_t::traits::element_size;

      return  combine ( load<typename target_t::substorage_type>(b, b1)
                      , load<typename target_t::substorage_type>(b1,b2)
                      );
    }

    // Other case: Fill a pack piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_(Begin const& b, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return target_t(b[N::value]...);
    }

    // Main entry point
    BOOST_FORCEINLINE target_t operator()(Begin const& b, End const&, Target const&) const
    {
      return do_(b, typename target_t::storage_kind(), typename target_t::traits::static_range{});
    }
  };
} } }

#endif
