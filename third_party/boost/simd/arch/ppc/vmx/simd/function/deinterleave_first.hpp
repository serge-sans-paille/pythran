//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DEINTERLEAVE_FIRST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char const shft = {0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30};
      return vec_perm(a0.storage(),a1.storage(),shft);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char const shft = {0,1,4,5,8,9,12,13,16,17,20,21,24,25,28,29};
      return vec_perm(a0.storage(),a1.storage(), shft);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_first_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::type32_<A0>, bs::vmx_>
                          , bs::pack_<bd::type32_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char const shft = {0,1,2,3,8,9,10,11,16,17,18,19,24,25,26,27};
      return vec_perm(a0.storage(),a1.storage(), shft);
    }
  };
} } }

#endif
