//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_FUNDAMENTAL_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_FUNDAMENTAL_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_fundamental \metafunction
 */

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //==============================================================================
  /*!
   * Checks if a given type is a fundamental type (i.e any scalar type natively
   * supported by C++).
   *
   * \par Model:
   *
   * \metafunction
   *
   * For any type \c T
   *
   * \code
   * typedef is_fundamental<T>::type r;
   * \endcode
   *
   * evaluates to \true_ if \c T hierarchy inherits from \c fundamental_<T>
   * and to \false_ otherwise
   *
   * \include is_fundamental.cpp
   */
  //==============================================================================
  template<class T>
  struct is_fundamental
  {
    typedef char true_type;
    struct false_type { char dummy[2]; };

    template<class X>
    static true_type call( meta::scalar_< meta::fundamental_<X> > );

    static false_type call(...);

    typedef typename meta::hierarchy_of<T>::type hierarchy;
    static const bool value = sizeof( call( hierarchy() ) ) == sizeof(true_type);
    typedef boost::mpl::bool_<value> type;
  };
} } }

#endif

