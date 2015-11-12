//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_DETAILS_ADAPTED_TRAITS_HPP_INCLUDED
#define BOOST_DISPATCH_META_DETAILS_ADAPTED_TRAITS_HPP_INCLUDED

#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost { namespace dispatch { namespace details
{
  struct is_floating_point_impl
  {
    template<class T> struct apply : boost::is_floating_point<T> {};
  };

  struct is_integral_impl
  {
    template<class T> struct apply : boost::is_integral<T> {};
  };
} } }

#endif
