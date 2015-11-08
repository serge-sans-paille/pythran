//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_PROXY_HPP_INCLUDED
#define BOOST_DISPATCH_META_PROXY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct proxy_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };
} } }

namespace boost { namespace dispatch { namespace details
{
  template<class Hierarchy> struct is_proxy : boost::mpl::false_ {};

  template<class T>
  struct is_proxy< meta::proxy_<T> >  : boost::mpl::true_ {};
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct  is_proxy
        : details::is_proxy< typename hierarchy_of<T>::type >
  {};
} } }

#endif
