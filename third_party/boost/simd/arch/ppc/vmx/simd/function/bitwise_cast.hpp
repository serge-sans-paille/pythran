//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::vmx_
                          , bs::pack_< bd::arithmetic_<A0>, bs::vmx_>
                          , bd::target_<bs::pack_<bd::arithmetic_<Target>, bs::vmx_>>
                          )
  {
    using target_t = typename Target::type;

    BOOST_FORCEINLINE target_t operator()(A0 const& a0, Target const&) const
    {
      return (typename target_t::storage_type)(a0.storage());
    }
  };
} } }

#endif
