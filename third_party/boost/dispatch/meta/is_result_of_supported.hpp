//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef BOOST_DISPATCH_META_IS_RESULT_OF_SUPPORTED_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_RESULT_OF_SUPPORTED_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::is_result_of_supported \metafunction
 */

#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/dispatch/meta/result_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  #if defined(DOXYGEN_ONLY)
  //============================================================================
  /*!
   * For a given type \c T describing a potential \c result_of function type,
   * this \metafunction verify that \c result_of is actually able to be resolved.
   *
   * \tparam T Function-type call to resolve
   *
   *  For any type \c T,
   *
   *  \code
   *  typedef boost::dispatch::meta::is_result_of_supported<T>::type r;
   *  \endcode
   *
   *  evaluates to \true_ if \c result_of<T>::type is defined.
   *
   * \include is_result_of_supported.cpp
   */
  //============================================================================
  template<class T, class Enable> struct is_result_of_supported {};
  #endif

  template<class T, class Enable=void>
  struct is_result_of_supported : boost::mpl::false_ {};

  template<class T>
  struct is_result_of_supported<T, typename enable_if_type< typename result_of<T>::type >::type>
   : boost::mpl::true_
  {
  };
} } }

#endif
