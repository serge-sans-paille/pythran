//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_FUNCTOR_META_HIERARCHY_HPP_INCLUDED
#define BOOST_DISPATCH_FUNCTOR_META_HIERARCHY_HPP_INCLUDED

/*!
 * \file
 * \brief Defines the basic evaluation context hierarchy for \ref boost::dispatch::functor
 */

#include <boost/dispatch/meta/details/hierarchy_base.hpp>

namespace boost { namespace dispatch { namespace tag
{
  //============================================================================
  /*!
   * \ingroup hierarchy
   * Defines the formal evaluation context for functors. This context is the
   * most abstract one and correspond to high-level code trasnformation function
   */
  //============================================================================
  struct formal_ : meta::unspecified_<formal_>
  {
    typedef meta::unspecified_<formal_> parent;
  };

  //============================================================================
  /*!
   * \ingroup hierarchy
   * Defines the CPU based evaluation context for functors. This context is used
   * when no specific architecture informations is available or required by a
   * \ref functor. Functors specialization under the \c cpu_ context is usually
   * used as common, architecture independant implementation.
   */
  //============================================================================
  struct cpu_ : formal_
  {
    typedef formal_ parent;
  };

  //============================================================================
  /*!
   * \ingroup hierarchy
   * Defines a dummy evaluation context equivalent to \c T.
   * This is used when combining sites.
   */
  //============================================================================
  template<class T>
  struct id_ : T
  {
    typedef T parent;
  };
} } }

#endif
