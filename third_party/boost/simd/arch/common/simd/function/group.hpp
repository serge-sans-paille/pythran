//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( group_
                            , (typename A0, typename X)
                            , (bd::is_downgradable<A0>)
                            , bd::cpu_
                            , bs::pack_<bd::fundamental_<A0>, X>
                            , bs::pack_<bd::fundamental_<A0>, X>
                            )
  {
    using result = bd::downgrade_t<A0>;

    template<typename... N>
    BOOST_FORCEINLINE result do_( const A0& a0, const A0& a1
                                , nsm::list<N...> const&
                                ) const BOOST_NOEXCEPT
    {
      using type = typename result::value_type;
      return result ( static_cast<type>(extract<N::value>(a0))...
                    , static_cast<type>(extract<N::value>(a1))...
                    );
    }

    BOOST_FORCEINLINE result operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return do_(a0,a1, typename A0::traits::element_range{});
    }
  };
} } }

#include <boost/simd/arch/common/simd/function/groups.hpp>

#endif

