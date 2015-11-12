//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_TRANSFER_QUALIFIERS_HPP_INCLUDED
#define BOOST_DISPATCH_META_TRANSFER_QUALIFIERS_HPP_INCLUDED

#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class U>
  struct transfer_qualifiers
  {
    typedef T type;
  };

  template<class T, class U>
  struct transfer_qualifiers<T, U&>
   : add_reference<T>
  {
  };

  template<class T, class U>
  struct transfer_qualifiers<T, U const>
   : add_const<T>
  {
  };

  template<class T, class U>
  struct transfer_qualifiers<T, U const&>
   : add_reference<typename add_const<T>::type>
  {
  };
} } }

#endif
