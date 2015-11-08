//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_EXTREMUM_CATEGORY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_EXTREMUM_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace container
{
  template<bool B> struct extremum;
} }

namespace boost { namespace dispatch { namespace meta
{
  //==========================================================================
  // extremum_ hierarchy is extremum_<T> -> unspecified_<T>
  //==========================================================================
  template<class T> struct  extremum_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  //==========================================================================
  // begin_/end_ hierarchy is extremum_<T>
  //==========================================================================
  template<bool IsEnd, class Origin>
  struct hierarchy_of<nt2::container::extremum<IsEnd>,Origin>
  {
    typedef extremum_<Origin> type;
  };
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::extremum_;
} }

#endif
