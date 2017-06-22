//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INTERLEAVE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/interleave_first.hpp>
#include <boost/simd/function/interleave_second.hpp>
#include <array>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( interleave_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<T>, X >
                          , bs::pack_< bd::unspecified_<T>, X >
                          )
  {
    static_assert ( T::static_size >= 2
                  , "interleave requires at least two elements"
                  );

    BOOST_FORCEINLINE std::array<T,2> operator()(T const& x, T const& y) const BOOST_NOEXCEPT
    {
      std::array<T,2> that{{ interleave_first(x,y), interleave_second(x,y) }};
      return that;
    }
  };
} } }

#endif
