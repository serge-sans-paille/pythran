//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_SCALAR_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_SCALAR_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_scalar \metafunction
 */

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Checks if a given Hierarchizable type is a scalar type.
   *
   * For any given Hierarchizable \c T,
   *
   * \code
   * typedef boost::dispatch::meta::is_scalar<T>::type r;
   * \endcode
   *
   * evaluates to \true_ is T has a hierarchy tied to \c scalar_
   *
   * \include is_scalar.cpp
   */
  //============================================================================
  template<class T>
  struct  is_scalar
  {
    typedef char true_type;
    struct false_type { char dummy[2]; };

    template<class X>
    static true_type call( meta::scalar_< meta::unspecified_<X> > );

    static false_type call(...);

    typedef typename meta::hierarchy_of<T>::type hierarchy;
    static const bool value = sizeof( call( hierarchy() ) ) == sizeof(true_type);
    typedef boost::mpl::bool_<value> type;
  };
} } }

#endif
