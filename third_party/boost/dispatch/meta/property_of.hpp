//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PROPERTY_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_PROPERTY_OF_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the boost::dispatch::meta::property_of \metafunction
 */

//////////////////////////////////////////////////////////////////////////////
// Types property is defined on fundamental types as a lattice of classes
// mimicking the type structuration in C++
//////////////////////////////////////////////////////////////////////////////

#include <boost/dispatch/meta/details/hierarchy_base.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/strip.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class Origin = T>
  struct property_of;
}

namespace details
{
  /// INTERNAL ONLY
  template<class T, class Origin = T, class Enable = void>
  struct  property_of
   : meta::property_of<T, Origin>
  {
  };

  /// INTERNAL ONLY
  template<class T, class sT, class Origin>
  struct property_of_impl
   : meta::property_of<sT, Origin>
  {
  };

  /// INTERNAL ONLY
  template<class T, class Origin>
  struct property_of_impl<T, T, Origin>
   : property_of<T, Origin>
  {
  };
}

namespace meta
{
  template<class T, class Origin>
  struct  property_of
#if !defined(DOXYGEN_ONLY)
        : details::property_of_impl< typename meta::strip<T>::type
                                   , typename meta::scalar_of<typename meta::strip<T>::type>::type
                                   , typename remove_reference<Origin>::type
                                   >
#endif
  {};

  /// INTERNAL ONLY
  template<class T, class Origin>
  struct  property_of<T&, Origin>
        : property_of<T, typename remove_reference<Origin>::type> {};

  /// INTERNAL ONLY
  template<class T, class Origin>
  struct  property_of<T const, Origin>
        : property_of<T, typename remove_reference<Origin>::type> {};
} } }

#include <boost/dispatch/meta/details/property_of.hpp>

#endif
