//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_NATIVE_CARDINAL_HPP_INCLUDED

#include <boost/mpl/size_t.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>

namespace boost { namespace simd
{
  template<class T> struct logical;

  namespace meta
  {
    template<class T>
    struct  native_cardinal
          : boost::mpl::size_t< BOOST_SIMD_BYTES / sizeof(T) > {};

    template<class T>
    struct  native_cardinal< logical<T> >
          : boost::mpl::size_t< BOOST_SIMD_BYTES / sizeof(T) > {};
  }
} }

#endif
