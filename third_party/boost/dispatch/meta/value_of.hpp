//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_VALUE_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_VALUE_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the \c value_of extension point
 */

#include <boost/dispatch/attributes.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct value_of;
}

namespace details
{
  template<class T, class Enable = void>
  struct value_of
  {
    typedef T type;
  };

  template<class T, class Enable = void>
  struct value_of_cv;

  template<class T, class Enable>
  struct value_of_cv<T const, Enable>
       : add_const<typename meta::value_of<T>::type>
  {
  };

  template<class T, class Enable>
  struct value_of_cv<T&, Enable>
       : add_reference<typename meta::value_of<T>::type>
  {
  };
}

namespace meta
{
  /*!
   * @brief Computes the basic value of a type
   *
   * @tparam T
   *
   *
   **/
  template<class T>
   struct value_of
        : details::value_of<T>
  {};

  /// INTERNAL ONLY
  template<class T>
  struct  value_of<T&>
        : details::value_of_cv<T&>
  {};

  /// INTERNAL ONLY
  template<class T>
  struct  value_of<T const>
        : details::value_of_cv<T const>
  {};

#ifndef BOOST_DISPATCH_NO_RESTRICT_REFERENCES
  /// INTERNAL ONLY
  template<class T>
  struct  value_of<T & BOOST_DISPATCH_RESTRICT>
        : details::value_of_cv<T&>
  {
  };
#endif
} } }

#endif
