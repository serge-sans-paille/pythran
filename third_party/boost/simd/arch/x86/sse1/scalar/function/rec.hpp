//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SCALAR_FUNCTION_REC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SCALAR_FUNCTION_REC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/refine_rec.hpp>
#include <boost/simd/function/raw.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( rec_
                          , (typename T)
                          , bs::sse_
                          , bs::raw_tag
                          , bd::scalar_<bd::single_<T>>
                          )
  {
    BOOST_FORCEINLINE T operator()(bs::raw_tag const&, T a0) const BOOST_NOEXCEPT
    {
      float inv;
      _mm_store_ss( &inv, _mm_rcp_ss( _mm_load_ss( &a0 ) ) );

      return inv;
    }
  };

} } }

#endif
