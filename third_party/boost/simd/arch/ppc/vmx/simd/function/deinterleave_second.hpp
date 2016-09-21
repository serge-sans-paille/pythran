//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DEINTERLEAVE_SECOND_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      __vector unsigned char const shft = {1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31};
      return vec_perm(a0.storage(),a1.storage(),shft);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const BOOST_NOEXCEPT
    {
      __vector unsigned char const shft = {2,3,6,7,10,11,14,15,18,19,22,23,26,27,30,31};
      return vec_perm(a0.storage(),a1.storage(),shft);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( deinterleave_second_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::type32_<A0>, bs::vmx_>
                          , bs::pack_<bd::type32_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A0 const& a1) const
    {
      __vector unsigned char const shft = {4,5,6,7,12,13,14,15,20,21,22,23,28,29,30,31};
      return vec_perm(a0.storage(),a1.storage(),shft);
    }
  };
} } }

#endif
