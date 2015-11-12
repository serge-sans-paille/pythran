//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_IS_SIGNED_HPP_INCLUDED
#define BOOST_DISPATCH_META_IS_SIGNED_HPP_INCLUDED

//////////////////////////////////////////////////////////////////////////////
// Return false or true depending on whether the primitive of T is signed or not
// See: http://nt2.metascale.org/sdk/meta/traits/is_signed.html
//////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct  is_signed
        : is_same < typename sign_of< typename primitive_of<T>::type >::type
                  , signed
                  >
  {};

  template<class T>
  struct  is_unsigned
        : is_same < typename sign_of< typename primitive_of<T>::type >::type
                  , unsigned
                  >
  {};
} } }

#endif
