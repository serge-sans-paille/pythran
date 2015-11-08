//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_TERMINAL_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_TERMINAL_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \c boost::dispatch::meta::terminal_of \metafunction
 */

#include <boost/config.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * \ingroup metafunctions
   * For any type, returns a type which can act as a proto terminal in an
   * expression template context
   *
   * \tparam Type type to convert into a terminal
   */
  template<class T> struct terminal_of { typedef T type; };

  template<class T> struct terminal_of<T const> : terminal_of<T> {};
  template<class T> struct terminal_of<T&> : terminal_of<T> {};
#ifndef BOOST_NO_RVALUE_REFERENCES
  template<class T> struct terminal_of<T&&> : terminal_of<T> {};
#endif

} } }

#endif
