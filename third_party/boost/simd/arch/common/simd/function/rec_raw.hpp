//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REC_RAW_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_REC_RAW_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/raw.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// raw_(rec) for floating types: 'take all' version when no speedier exists
  /// on some architectures an intrinsic is called providing few bits and/or not getting correct
  /// results for zeros denormals  and infinities (sse1, sse2, avx)
  /// These version are used as bases for improvement using Newton Raphson and correcting limits
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  BOOST_DISPATCH_OVERLOAD_IF( rec_
                            , (typename T, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::raw_tag
                            , bs::pack_<bd::unspecified_<T>, X>
                            )
  {
    BOOST_FORCEINLINE T operator()(const raw_tag &, T const& a) const BOOST_NOEXCEPT
    {
      return rec(a);
    }
  };
} } }

#endif
