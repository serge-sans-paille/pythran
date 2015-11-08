//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/U.B.P
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_MAKE_DEPENDENT_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_MAKE_DEPENDENT_HPP_INCLUDED

namespace boost { namespace simd { namespace meta
{
  /**
   * make_dependent hides a concrete type into a type-dependent construct
   * to prevent spurious template instanciation
   **/
  template <class T, class U> struct make_dependent
  {
    typedef T type;
  };
} } }

#endif
