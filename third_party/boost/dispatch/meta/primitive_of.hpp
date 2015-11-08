//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PRIMITIVE_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_PRIMITIVE_OF_HPP_INCLUDED
/*!
 * \file
 * \brief Defines the boost::dispatch::meta::primitive_of @metafunction
 */
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace dispatch { namespace details
{
  /// INTERNAL ONLY
  template<class T, class Origin>
  struct primitive_of_impl
    : mpl::identity< primitive_of_impl<typename meta::value_of<T>::type, T> >::type
  {
  };

  /// INTERNAL ONLY
  template<class T> struct primitive_of_impl<T, T>
  {
     typedef T type;
  };
}

namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * For a given Hierarchizable type T, returns the underlying type used to
   * define T
   *
   * \tparam Hierarchizable Type to extract a primitive from.
   *
   * \par Models:
   * \metafunction
   *
   * \par Semantic:
   * For a given Hierarchizable type T,
   *
   * \code
   * typedef primitive_of<T>::type r;
   * \endcode
   *
   * is defined so that
   *
   * \code
   * is_same<T, apply<factory_of<T>,r>::type>::value == true
   * \endcode
   *
   * \include primitive_of.cpp
   */
  //============================================================================
  template<class T>
  struct primitive_of
  #if !defined(DOXYGEN_ONLY)
    : details::primitive_of_impl<typename value_of<T>::type, T>
  #endif
  {
  };
} } }

#endif
