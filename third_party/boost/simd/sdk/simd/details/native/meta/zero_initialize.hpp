//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_ZERO_INITIALIZE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_META_ZERO_INITIALIZE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>
#include <boost/simd/sdk/meta/zero_initialize.hpp>

namespace boost { namespace simd { namespace meta
{
  template<typename T, typename X>
  struct zero_initialize< native<T, X> >
  {
    static BOOST_FORCEINLINE native<T, X> call()
    {
      typename native<T, X>::native_type n = {};
      return native<T, X>(n);
    }
  };
} } }

#endif
