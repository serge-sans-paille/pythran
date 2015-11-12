//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_GENERIC_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_GENERIC_HPP_INCLUDED

#include <boost/dispatch/meta/details/hierarchy_base.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct fusion_sequence_;

  template<class T>
  struct generic_ : generic_< typename T::parent >
  {
    typedef generic_< typename T::parent >  parent;
  };

  template<class T>
  struct generic_< unspecified_<T> > : mpl::if_< boost::fusion::traits::is_sequence< typename meta::scalar_of<T>::type >, fusion_sequence_<T>, unspecified_<T> >::type
  {
    typedef typename mpl::if_< boost::fusion::traits::is_sequence< typename meta::scalar_of<T>::type >, fusion_sequence_<T>, unspecified_<T> >::type parent;
  };
} } }

#include <boost/dispatch/meta/fusion.hpp>

#endif
