//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_COLON_CATEGORY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_COLON_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace container
{
  struct colon_;
} }

namespace boost { namespace dispatch { namespace meta
{
  //==========================================================================
  // colon_ hierarchy is colon_<T> -> unspecified_<T>
  //==========================================================================
  template<class T> struct  colon_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  //==========================================================================
  // colon_ hierarchy is colon_<T>
  //==========================================================================
  template<class Origin> struct hierarchy_of<nt2::container::colon_,Origin>
  {
    typedef colon_<Origin> type;
  };
} } }

namespace nt2 { namespace ext
{
  using boost::dispatch::meta::colon_;
} }

#endif
