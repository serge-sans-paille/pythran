//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_TIEABLE_HPP_INCLUDED
#define BOOST_DISPATCH_META_TIEABLE_HPP_INCLUDED

#include <boost/dispatch/meta/details/hierarchy_base.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Tie-able node hierarchy
  //============================================================================
  template<class Tag> struct tieable_ : unspecified_<Tag>
  {
    typedef unspecified_<Tag> parent;
  };
} } }

#endif
