//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_TERMINAL_OF_SHARED_HPP_INCLUDED
#define BOOST_DISPATCH_META_TERMINAL_OF_SHARED_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \c boost::dispatch::meta::terminal_of_shared \metafunction
 */

#include <boost/config.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * \ingroup metafunctions
   * For any type, returns a type which can act as a proto terminal in an
   * expression template context and which does shallow copies.
   * Must also provide a make function for construction.
   *
   * \tparam Type type to convert into a terminal
   */
  template<class T> struct terminal_of_shared
  {
    typedef typename meta::terminal_of<T>::type type;
    static type make() { return type(); }
  };

  template<class T> struct terminal_of_shared<T const> : terminal_of_shared<T> {};
  template<class T> struct terminal_of_shared<T&> : terminal_of_shared<T> {};
#ifndef BOOST_NO_RVALUE_REFERENCES
  template<class T> struct terminal_of_shared<T&&> : terminal_of_shared<T> {};
#endif

} } }

#endif
