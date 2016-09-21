//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/constant/mzero.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/dispatch/meta/as_unsigned.hpp>
#include <boost/predef/compiler.h>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::single_<A0>, bs::vmx_>
                          , bs::pack_<bd::single_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_madd(a0.storage(),a1.storage(), bs::Mzero<A0>().storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::type16_<A0>, bs::vmx_>
                          , bs::pack_<bd::type16_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return vec_mladd(a0.storage(),a1.storage(),Zero<A0>().storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::type8_<A0>, bs::vmx_>
                          , bs::pack_<bd::type8_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      auto l = vec_mule(a0.storage(),a1.storage());
      auto r = vec_mulo(a0.storage(),a1.storage());
      return vec_mergel(vec_pack(l,l),vec_pack(r,r));
    }
  };

  #if BOOST_COMP_CLANG || BOOST_COMP_GNUC
  BOOST_DISPATCH_OVERLOAD ( multiplies_
                          , (typename A0)
                          , bs::vmx_
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          , bs::pack_<bd::ints32_<A0>, bs::vmx_>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      return a0.storage() * a1.storage();
    }
  };
  #endif
} } }

#endif
