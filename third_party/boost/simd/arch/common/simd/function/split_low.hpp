//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_LOW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLIT_LOW_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/detail/dispatch/meta/upgrade.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( split_low_
                            , (typename A0, typename X)
                            , (bd::is_upgradable<A0>)
                            , bd::cpu_
                            , bs::pack_<bd::unspecified_<A0>, X>
                            )
  {
    using result_t = bd::upgrade_t<A0>;

    template<typename... N>
    static BOOST_FORCEINLINE result_t do_(A0 const& a, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      using type = typename result_t::value_type;
      return result_t( static_cast<type>(bs::extract<N::value>(a))... );
    }

    BOOST_FORCEINLINE result_t operator()(A0 const& a) const BOOST_NOEXCEPT
    {
      return do_(a, typename result_t::traits::element_range{});
    }
  };
} } }

#endif
