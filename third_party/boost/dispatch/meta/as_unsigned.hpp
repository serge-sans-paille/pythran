//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_UNSIGNED_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_UNSIGNED_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::as_unsigned @metafunction.
 **/

#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>
#include <boost/dispatch/meta/details/as_unsigned.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Compute the unsigned equivalent of a given type
   *
   * Returns the input type rebound the unsigned equivalent type to its primitive
   * type.
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
   * typedef as_unsigned<T>::type type;
   * @endcode
   *
   * is equivalent to
   *
   * @code
   * typedef T  type;
   * @endcode
   *
   * if @c primitive<T>::type is @c unsigned and to
   *
   * @code
   *  typedef apply< meta::factory_of<T>::type
   *               , boost::make_unsigned< meta::primitive_of<T>::type >::type
   *               >::type                                                type;
   * @endcode
   *
   * if @c primitive<T>::type is signed. Note than for this @metafunction,
   * real types like @c double or @c float are considered signed.
   *
   * @par Example usage:
   *
   * @include as_unsigned.cpp
   */
#if defined(DOXYGEN_ONLY)
  template<typename T> struct as_unsigned {};
#else
  template<typename T>
  struct  as_unsigned
        : details::as_unsigned_impl< typename meta::strip<T>::type >
  {
    //**************************** STATIC ASSERT *****************************//
    //     A type with a non-fundamental primitive is used in a call to the   //
    //            boost::dispatch::meta::as_unsigned meta-function.           //
    //**************************** STATIC ASSERT *****************************//
    BOOST_MPL_ASSERT_MSG
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_UNSIGNED
    , (T&)
    );
  };
#endif
} } }

#endif
