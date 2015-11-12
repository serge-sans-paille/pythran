//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/U.B.P
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_ZERO_INITIALIZE_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_ZERO_INITIALIZE_HPP_INCLUDED

#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace meta
{
  /**
   * zero_initialize is an extension point for zero-initialization of
   * non-POD types
   **/
  template<class T>
  struct zero_initialize
  {
    static BOOST_FORCEINLINE T call()
    {
      return T();
    }
  };
} } }

#endif
