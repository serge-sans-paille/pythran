//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_SCALAR_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_SCALAR_OF_HPP_INCLUDED

#include <boost/dispatch/meta/value_of.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch { namespace meta
{
  /**
   * @brief scalar_of metafunction
   *
   * scalar_of computes ....
  **/
  template<class T> struct scalar_of
  {};
} } }
#else
namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct scalar_of;
}

namespace details
{
  template<class T, class U = typename meta::value_of<T>::type>
  struct scalar_of
    : meta::scalar_of<U>
  {
  };

  template<class T>
  struct scalar_of<T, T>
  {
    typedef T type;
  };
}

namespace meta
{
  template<class T>
  struct  scalar_of
        : details::scalar_of<T> {};

  template<class T>
  struct scalar_of<T&>
    : mpl::if_< is_same< typename meta::scalar_of<T>::type
                       , T
                       >
              , T&
              , typename details::scalar_of<T&>::type
              >
  {
  };

  template<class T>
  struct scalar_of<T const>
    : mpl::if_< is_same< typename meta::scalar_of<T>::type
                       , T
                       >
              , T const
              , typename details::scalar_of<T const>::type
              >
  {
  };
} } }

#endif

#endif
