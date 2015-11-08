//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_IS_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_IS_LOGICAL_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

namespace boost { namespace simd
{
  template<class T>
  struct logical;

namespace meta
{
  template<class T>
  struct is_logical : boost::mpl::false_ {};

  template<class T>
  struct is_logical<boost::simd::logical<T> > : boost::mpl::true_ {};

  template<class T, class Ext>
  struct is_logical<boost::simd::native<T, Ext> > : is_logical<T> {};
} } }

#endif
