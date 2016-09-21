//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_GAMMALN_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/gammaln.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( gammaln_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      return {bs::gammaln(a0[0]), bs::gammaln(a0[1])};

    }
  };

} } }

#endif
