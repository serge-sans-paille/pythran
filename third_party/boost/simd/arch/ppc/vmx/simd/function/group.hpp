//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_GROUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_GROUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE
    bd::downgrade_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_pack(a0.storage(), a1.storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE
    bd::downgrade_t<A0> operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_pack(a0.storage(), a1.storage());
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Saturated group
  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::vmx_
                          , bs::saturated_tag
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(bs::saturated_tag const&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_packs(a0.storage(), a1.storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( group_
                          , (typename A0)
                          , bs::vmx_
                          , bs::saturated_tag
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE bd::downgrade_t<A0>
    operator()(bs::saturated_tag const&, const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_packs(a0.storage(), a1.storage());
    }
  };
} } }

#endif
