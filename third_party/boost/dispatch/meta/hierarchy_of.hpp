//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_HIERARCHY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_HIERARCHY_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the hierarchy building classes and \metafunction
 */

//////////////////////////////////////////////////////////////////////////////
// Types hierarchy defines a partially order lattice of type familly
// which helps categorizing a given type into all its potential enclosing type
// sets. Hierarchies are template so they can use their root type to
// select at each lattice node which ancestor to use.
//////////////////////////////////////////////////////////////////////////////

#include <boost/dispatch/meta/details/hierarchy_base.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace dispatch { namespace details
{
  /// INTERNAL ONLY
  template<class T, class Origin = T, class Enable = void>
  struct  hierarchy_of
  {
    typedef typename remove_const<Origin>::type stripped;
    typedef typename mpl::if_ < is_same< T, stripped >
                              , stripped
                              , Origin
                              >::type           origin_;
    typedef meta::unspecified_<origin_>         type;
  };
}

namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // hierarchy_of computes the entry point of a given type inside the type
  // hierarchy lattice.
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Origin = T>
  struct  hierarchy_of
#if !defined(DOXYGEN_ONLY)
        : details::hierarchy_of< T
                               , typename remove_reference<Origin>::type
                               >
#endif
  {};

  /// INTERNAL ONLY
  template<class T, class Origin>
  struct  hierarchy_of<T&, Origin>
        : hierarchy_of<T, typename remove_reference<Origin>::type> {};

  /// INTERNAL ONLY
  template<class T, class Origin>
  struct  hierarchy_of<T const, Origin>
        : hierarchy_of<T, typename remove_reference<Origin>::type> {};
} } }

#include <boost/dispatch/meta/details/hierarchy_of.hpp>

#endif
