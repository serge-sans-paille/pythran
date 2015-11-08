//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_NA_HPP_INCLUDED
#define BOOST_DISPATCH_META_NA_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the boost::dispatch::meta::na_ type
 */

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Empty type used to represent empty elements in compile-time containers.
   * boost::dispatch::meta::na_ is used in nt2 to prevent some ADL issues with Boost.MPL.
   */
  //============================================================================
  struct na_ {};
} } }

#endif
