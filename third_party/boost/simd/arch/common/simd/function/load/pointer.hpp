//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_POINTER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOAD_POINTER_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // load from a pointer of whatever in a pack
  // This case also handles "load with cast" behavior
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Target, typename Pointer, typename Ext)
                          , bd::cpu_
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    BOOST_FORCEINLINE target_t operator()(Pointer p, Target const&) const BOOST_NOEXCEPT
    {
      return do_(p, typename target_t::storage_kind(), typename target_t::traits::static_range{} );
    }

    // Aggregate case: fill in the storage by calling load twice
    template<typename... N> static BOOST_FORCEINLINE
    target_t do_(Pointer p, aggregate_storage const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return combine( load<typename storage_t::value_type>(p)
                    , load<typename storage_t::value_type>(p+target_t::traits::element_size)
                    );
    }

    // Other case: Fill a pack piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    target_t do_(Pointer p, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return target_t(static_cast<typename target_t::value_type>(p[N::value])...);
    }
  };
} } }

#endif
