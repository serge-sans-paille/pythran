//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_NTH_HIERARCHY_HPP_INCLUDED
#define BOOST_DISPATCH_META_NTH_HIERARCHY_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::nth_hierarchy traits.
 **/

#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch
{
  namespace details
  {
    template<class T, int N> struct nth_hierarchy
    {
      typedef typename nth_hierarchy<T,N-1>::type base;
      typedef typename base::parent           type;
    };

    template<class T>
    struct nth_hierarchy<T,0> : boost::dispatch::meta::hierarchy_of<T>
    {};
  }

  namespace meta
  {
    /*!
     *
     **/
    template<class T, class N>
    struct nth_hierarchy : details::nth_hierarchy<T,N::value>
    {};
  }
} }

#endif


