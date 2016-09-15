//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SORT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SORT_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/function/max.hpp>
#include <boost/simd/function/min.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  BOOST_DISPATCH_OVERLOAD ( sort_
                          , (typename A0)
                          , bs::sse1_
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE A0 operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      // half-permute
      A0 p0 = shuffle<2,3,0,1>(a0);
      A0 mn = min(a0,p0);
      A0 mx = max(a0,p0);
      // cross vector concatenation and reversal
      A0 minmax = shuffle<0,1,6,7>(mn,mx);
      A0 maxmin = shuffle<1,0,7,6>(mn,mx);

      mn = min(minmax,maxmin);
      mx = max(minmax,maxmin);

      // rearrange partial max/min while keeping min and max in place
         p0 = shuffle<0,2,5,7>(mn,mx);
      A0 p1 = shuffle<0,2,1,3>(p0);

      // Bring sorted min/max in the proper place
      return shuffle<0,1,6,7>(min(p1,p0),max(p1,p0));
    }
  };
} } }

#endif

