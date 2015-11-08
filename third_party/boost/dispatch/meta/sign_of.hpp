//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_SIGN_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_SIGN_OF_HPP_INCLUDED

#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/type_traits/is_floating_point.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*! Computes the signedness of a given type.
   *
   * \tparam T Type to compute signedness from.
   * \return If \c T is signed, \c sign_of<T>::type is \c signed, otherwsie, it
   * is \c unsigned.
   **/
  //============================================================================
  template<class T> struct sign_of;
} } }

namespace boost { namespace dispatch { namespace ext
{
  template<class T, class Enable = void>
  struct  sign_of
        : sign_of< typename meta::primitive_of<T>::type >
  {};

  template<class T>
  struct sign_of<T, typename enable_if< boost::is_signed<T> >::type>
  {
    typedef signed type;
  };

  template<class T>
  struct sign_of<T, typename enable_if< boost::is_unsigned<T> >::type>
  {
    typedef unsigned type;
  };

  template<class T>
  struct sign_of<T, typename enable_if< boost::is_floating_point<T> >::type>
  {
    typedef signed type;
  };
} } }

namespace boost { namespace dispatch { namespace meta
{
  template<class T> struct  sign_of           : ext::sign_of<T> {};
  template<class T> struct  sign_of<T&>       : sign_of <T>     {};
  template<class T> struct  sign_of<T const>  : sign_of <T>     {};
} } }
#endif
