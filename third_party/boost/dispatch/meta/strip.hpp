//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_STRIP_HPP_INCLUDED
#define BOOST_DISPATCH_META_STRIP_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the boost::dispatch::meta::strip \metafunction
 */

#include <boost/config.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Removes all reference and cv-qualifier from a given type \c T.
   *
   * \tparam T Type to strip from reference and cv-qualifier.
   *
   * For any given type \c T,
   *
   * \code
   * typedef boost::dispatch::meta::strip<T>::type r;
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef remove_cv< remove_reference<T>::type >::type r;
   * \endcode
   *
   * \include strip.cpp
   */
  //============================================================================
  template<class T> struct strip                      { typedef T type; };
  template<class T> struct strip<T const            > : strip<T> {};
  template<class T> struct strip<T volatile         > : strip<T> {};
  template<class T> struct strip<T const volatile   > : strip<T> {};
  template<class T> struct strip<T &                > : strip<T> {};
#ifndef BOOST_NO_RVALUE_REFERENCES
  template<class T> struct strip<T &&               > : strip<T> {};
#endif

  //============================================================================
  // strip on C-style array
  //============================================================================
  template<class T, std::size_t N>
  struct strip<T[N]> { typedef typename strip<T>::type type[N]; };

  template<class T, std::size_t N>
  struct strip<T const[N]> { typedef typename strip<T>::type type[N]; };
} } }

#endif
