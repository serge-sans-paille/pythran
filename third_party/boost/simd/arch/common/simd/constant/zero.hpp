//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_CONSTANT_ZERO_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_CONSTANT_ZERO_HPP_INCLUDED

#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;

  BOOST_DISPATCH_OVERLOAD ( zero_
                          , (typename T, typename X)
                          , bd::cpu_
                          , bd::target_<bs::pack_<bs::logical_<T>,X>>
                          )
  {
    BOOST_FORCEINLINE typename T::type operator()(T const&) const BOOST_NOEXCEPT
    {
      return typename T::type( typename T::type::value_type(false) );
    }
  };
} } }

#endif
