//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_REPEAT_LOWER_HALF_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_REPEAT_LOWER_HALF_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( repeat_lower_half_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::fundamental_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0) const
    {
      __vector unsigned char const shft = { 0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7 };
      return vec_perm(a0.storage(),a0.storage(),shft);
    }
  };
} } }

#endif
