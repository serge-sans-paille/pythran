//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/saturated.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( toint_
                          , (typename A0)
                          , bs::vmx_
                          , bs::saturated_tag
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
  {
    using result =  bd::as_integer_t<A0>;

    BOOST_FORCEINLINE result operator()(bs::saturated_tag const&, const A0& a0) const BOOST_NOEXCEPT
    {
      return vec_cts(a0.storage(),0);
    }
  };
} } }

#endif
