//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SCALAR_FUNCTION_INEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SCALAR_FUNCTION_INEARBYINT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/is_nan.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( inearbyint_
                          , (typename A0)
                          , bs::sse2_
                          , bd::scalar_<bd::double_<A0>>
                          )
  {
    BOOST_FORCEINLINE  bd::as_integer_t<A0> operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return _mm_cvtsd_si64(_mm_set_sd(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( inearbyint_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pedantic_tag
                          , bd::scalar_<bd::double_<A0>>
                          )
  {
    using iA0 = bd::as_integer_t<A0>;
    BOOST_FORCEINLINE iA0 operator() (bs::pedantic_tag const&
                                     , const A0 & a0) const BOOST_NOEXCEPT
    {
      if (BOOST_UNLIKELY(is_nan(a0))) return Zero<iA0>();
      if (BOOST_UNLIKELY(a0 == Inf<A0>())) return Valmax<iA0>();
      return _mm_cvtsd_si64(_mm_set_sd(a0));
    }
  };

} } }

#endif
