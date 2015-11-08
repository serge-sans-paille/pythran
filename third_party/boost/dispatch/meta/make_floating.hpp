 //==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_MAKE_FLOATING_HPP_INCLUDED
#define BOOST_DISPATCH_META_MAKE_FLOATING_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Meta-function that creates a standard real type from a size in bytes.
// As all make_xxx, also provides an optional lambda to apply to the result.
// See: http://nt2.metascale.org/sdk/meta/traits/make_floating.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/na.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<std::size_t Size, class Transform = na_>
  struct  make_floating
        : boost::mpl::apply<Transform,float> {};

  template<> struct  make_floating<sizeof(double) , na_ > { typedef double  type; };
  template<> struct  make_floating<sizeof(float)  , na_ > { typedef float   type; };

  template<class Transform>
  struct  make_floating<sizeof(double),Transform>
        : boost::mpl::apply<Transform,double> {};

  template<class Transform>
  struct  make_floating<sizeof(float),Transform>
        : boost::mpl::apply<Transform,float> {};
} } }

#endif
