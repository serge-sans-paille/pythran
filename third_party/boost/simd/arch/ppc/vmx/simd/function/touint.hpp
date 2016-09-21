//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOUINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_TOUINT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( touint_
                          , (typename A0)
                          , bs::vmx_
                          , bs::saturated_tag
                          , bs::pack_< bd::single_<A0>, bs::vmx_>
                          )
   {
      BOOST_FORCEINLINE  bd::as_integer_t<A0, unsigned>
      operator()(bs::saturated_tag const&, const A0& a0) const BOOST_NOEXCEPT
      {
        return vec_ctu(a0.storage(),0);
      }
   };
} } }

#endif
