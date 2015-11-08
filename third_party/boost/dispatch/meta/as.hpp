//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::as_ type wrapper.
 **/

#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * Type wrapper hierarchy.
   *
   * @par Models:
   *
   * Hierarchy
   *
   * @tparam T Wrapped type hierarchy
   */
  //============================================================================
  template<class T> struct target_{};
} } }
#else
BOOST_DISPATCH_REGISTER_HIERARCHY(target_)
#endif

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Lightweight type wrapper.
   *
   * Some implementation details of NT2 require types to be wrapped into an
   * empty structure so the type can be passed as a "ghostly" instance.
   * as_ performs such a wrapping.
   *
   * To discriminate as_ from the type @c T it wraps, its hierarcy is defined as
   * @c target_<hierarchy_of<T>::type>
   *
   * @par Models:
   *
   * @metafunction
   */
  template<class T>
  struct as_
  {
    typedef T type;
  };

  template<class T>
  struct target_value
  {
    typedef T type;
  };

  template<class T>
  struct target_value< as_<T> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY
  /// Register as_ hierarchy
  template<class T, class Origin>
  struct hierarchy_of< as_<T>, Origin>
  {
    typedef typename remove_const<Origin>::type               stripped;
    typedef typename mpl::if_ < is_same< stripped, as_<T> >
                              , stripped
                              , Origin
                              >::type                         origin_;
    typedef target_<typename hierarchy_of<T, origin_>::type>  type;
  };

  /// INTERNAL ONLY
  /// The value of as_<T> is T
  template<class T>
  struct value_of< as_<T> >
  {
    typedef T type;
  };

  /// INTERNAL ONLY
  template<class T>
  struct model_of< as_<T> >
  {
    struct type
    {
      template<class X> struct apply { typedef as_<X> type; };
    };
  };
} } }

#endif
