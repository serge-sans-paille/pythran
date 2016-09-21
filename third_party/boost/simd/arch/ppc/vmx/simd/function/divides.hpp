//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_DIVIDES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/rec.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( divides_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::single_<A0>, bs::vmx_>
                          , bs::pack_<bd::single_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_madd(a0.storage(),rec(a1).storage(),Zero<A0>().storage());
    }
  };
} } }

#endif
