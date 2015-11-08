//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ADAPTED_TRAITS_HPP_INCLUDED
#define BOOST_DISPATCH_META_ADAPTED_TRAITS_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::is_floating_point and
 * boost::dispatch::meta::is_integral traits.
 **/

#include <boost/dispatch/meta/behave_as.hpp>
#include <boost/dispatch/meta/details/adapted_traits.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Check primitive type for floating point behavior
   *
   * For any type @c T, checks if its primitive type is a floating-point type.
   *
   * @tparam T Any type
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   * For any type @c T,
   *
   * @code
   * typedef is_floating<T>::type type;
   * @endcode
   *
   * is equivalent to
   *
   * @code
   * typedef behave_as< boost::is_floating_point<boost::mpl::_>, T > type;
   * @endcode
   **/
  template<class T>
  struct  is_floating_point
        : behave_as  < details::is_floating_point_impl
                     , T
                     >
  {};

  /*!
   * @brief Check primitive type for integer behavior
   *
   * For any type @c T, checks if its primitive type is an integral type.
   *
   * @tparam T Any type
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   * For any type @c T,
   *
   * @code
   * typedef is_integral<T>::type type;
   * @endcode
   *
   * is equivalent to
   *
   * @code
   * typedef behave_as< boost::is_integral<boost::mpl::_>, T > type;
   * @endcode
   **/
  template<class T>
  struct  is_integral
        : behave_as  < details::is_integral_impl
                     , T
                     >
  {};
} } }

#endif
