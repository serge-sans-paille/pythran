//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_AS_INTEGER_HPP_INCLUDED
#define BOOST_DISPATCH_META_AS_INTEGER_HPP_INCLUDED

/*!
 * @file
 * @brief Define the boost::dispatch::meta::as_integer @metafunction.
 **/

#include <boost/mpl/assert.hpp>
#include <boost/dispatch/meta/sign_of.hpp>
#include <boost/dispatch/meta/factory_of.hpp>
#include <boost/dispatch/meta/make_integer.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>
#include <boost/dispatch/meta/is_fundamental.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief Compute the integral equivalent of a given type
   *
   * Computes an integral type which is compatible with the input type @c T and
   * with a given signedness  @c Signed.
   *
   * @tparam T    Type to transform
   * @tparam Sign Signedness of expected output. By default, the signedness
   * of @c T
   *
   * @par Models:
   *
   * @metafunction
   *
   * @par Semantic:
   *
   * For any type @c T and @c Sign,
   *
   * @code
   * typedef as_integer<T, Sign>::type type;
   * @endcode
   *
   * is equivalent to:
   *
   * @code
   *  typedef make_integer< sizeof(primitive_of<T>::type)
   *                      , Sign
   *                      , factory_of<T>::type
   *                      >::type                           type;
   * @endcode
   *
   * If any of the Ai is not a Primitive type, a
   * @c BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_INTEGER static
   * assertion is triggered.
   *
   * @par Usage:
   *
   * @include as_integer.cpp
   */
#if defined(DOXYGEN_ONLY)
  template<class T, class Sign = typename meta::sign_of<T>::type >
  struct  as_integer
  {};
#else
  template<class T, class Sign = typename meta::sign_of<T>::type >
  struct  as_integer
        : meta::
          make_integer< sizeof( typename meta::
                                primitive_of<typename meta::strip<T>::type>::type
                              )
                      , Sign
                      , typename meta::
                        factory_of<typename meta::strip<T>::type>::type
                      >
  {
    //**************************** STATIC ASSERT *****************************//
    //     A type with a non-fundamental primitive is used in a call to the   //
    //             boost::dispatch::meta::as_integer meta-function.           //
    //**************************** STATIC ASSERT *****************************//
    BOOST_MPL_ASSERT_MSG
    ( (is_fundamental < typename
                        meta::primitive_of<typename meta::strip<T>::type>::type
                      >::value
      )
    , BOOST_DISPATCH_NON_FUNDAMENTAL_PRIMITIVE_USED_IN_META_AS_INTEGER
    , (T&)
    );
  };
#endif
} } }

#endif
