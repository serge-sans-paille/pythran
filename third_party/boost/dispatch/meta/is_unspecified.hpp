//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_UNSPECIFIED_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_UNSPECIFIED_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Is T an unsepcified type ?
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  is_unspecified
        : boost::is_same< typename hierarchy_of<T>::type
                        , unspecified_<T>
                        >
  {};
} } }

#endif

