//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_SCALAR_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_SCALAR_HPP_INCLUDED

#include <boost/dispatch/meta/details/generic.hpp>
#include <boost/dispatch/meta/property_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct scalar_ : scalar_< typename T::parent >
  {
    typedef scalar_< typename T::parent > parent;
  };

  template<class T>
  struct  scalar_< unspecified_<T> >
        : generic_< typename property_of<T>::type >
  {
    typedef generic_< typename property_of<T>::type > parent;
  };
} } }

#endif
