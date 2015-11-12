//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_UNPROXY_HPP_INCLUDED
#define BOOST_DISPATCH_META_UNPROXY_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the unproxify function
**/

#include <boost/fusion/include/copy.hpp>
#include <boost/dispatch/meta/proxy.hpp>

namespace boost { namespace dispatch
{
  namespace meta
  {
    /*!
      @brief Metafunction computing the concrete type associated to a potential
      proxy type.
    **/
    template<class T> struct unproxy
    {
      template<class U> struct value_ { typedef typename U::value_type type; };

      typedef typename mpl::eval_if < is_proxy<T>
                                    , value_<T>
                                    , mpl::identity<T&>
                                    >::type         type;
    };
  }

  /*!
    @brief Unproxify a value

    For any given value @c t of type @c T, return either @c t if @c T is not a
    proxy type or a value of the concrete type of @c T if @c T is a proxy type.

    @param t Value to unproxify
  **/
  template<class T>
  BOOST_FORCEINLINE typename meta::unproxy<T const>::type unproxy(T const& t)
  {
    return t;
  }

  template<class T>
  BOOST_FORCEINLINE typename meta::unproxy<T>::type unproxy(T& t)
  {
    return t;
  }
} }

#endif
