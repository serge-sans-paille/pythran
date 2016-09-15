//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::vmx_
                          , bs::pack_< bd::arithmetic_<A0>, bs::vmx_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const
    {
      return do_(a0, brigand::bool_<A1::value >= 0 && A1::value < A0::static_size>{});
    }

    BOOST_FORCEINLINE A0 do_(A0 const& a0, std::true_type const&) const
    {
      return vec_splat(a0.storage(), A1::value );
    }

    BOOST_FORCEINLINE A0 do_(A0 const& a0, std::false_type const&) const
    {
      return vec_xor(a0.storage(),a0.storage());
    }
  };
} } }

#endif
