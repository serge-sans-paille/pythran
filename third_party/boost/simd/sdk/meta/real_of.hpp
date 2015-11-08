//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_META_REAL_OF_HPP_INCLUDED
#define BOOST_SIMD_SDK_META_REAL_OF_HPP_INCLUDED

#include <boost/dispatch/meta/value_of.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct real_of;
}

namespace details
{
  template<class T, class U = typename boost::dispatch::meta::value_of<T>::type>
  struct real_of
    : meta::real_of<U>
  {
  };

  template<class T>
  struct real_of<T, T>
  {
    typedef T type;
  };
}

namespace meta
{
  template<class T>
  struct  real_of
        : details::real_of<T> {};

  template<class T>
  struct real_of<T&>
    : boost::mpl::if_< boost::is_same< typename meta::real_of<T>::type
                                     , T
                                     >
                     , T&
                     , typename details::real_of<T&>::type
                     >
  {
  };

  template<class T>
  struct real_of<T const>
    : boost::mpl::if_< boost::is_same< typename meta::real_of<T>::type
                                     , T
                                     >
                     , T const
                     , typename details::real_of<T const>::type
                     >
  {
  };
} } }

#endif
