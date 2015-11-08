//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_REF_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_REF_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::as_ref @metafunction.
 **/

namespace boost { namespace dispatch { namespace meta
{
    /*!
   * @brief Adapt a type to be a suitable parameters of dispatching function
   *
   * Returns a type which is equivalent to @c T but which will be properly
   * qualified for dispacthing resolution.
   *
   * @tparam T Type to modify
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   *
   * For any type @c T,
   *
   * @code
   * typedef as_ref<T>::type type;
   * @endcode
   *
   * is equivalent to
   *
   * @code
   * typedef T& type;
   * @endcode
   *
   * if @c T is a reference type and to
   *
   * @code
   *  typedef T const& type;
   * @endcode
   *
   * otherwise.
   */
  template<class T> struct as_ref
  {
    typedef T const& type;
  };

  /// INTERNAL ONLY
  template<class T> struct as_ref<T&>
  {
    typedef T& type;
  };

  /// INTERNAL ONLY
  template<class T>
  struct as_ref<T const>
  {
    typedef T const& type;
  };
} } }

#endif
