//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED
#define BOOST_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED

/*!
 * @file
 * @brief Defines the @ref boost::dispatch::meta::behave_as @metafunction
 */

#include <boost/mpl/apply.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/primitive_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  /*!
   * @brief @mpllambda forwarding on Hierarchizable types
   *
   * Forward the application of a given @mpllambda @c Lambda onto a
   * fundamental type.
   *
   * @tparam Lambda @mpllambda to apply.
   * @tparam T      Fundamental type to transform
   *
   * @par Semantic:
   *
   * For any type @c T and any @mpllambda @c Lambda:
   *
   * @code
   * typedef boost::dispatch::meta::behave_as<Lambda,T>::type r;
   * @endcode
   *
   * is equivalent to:
   *
   * @code
   * typedef apply1 < Lambda
   *                , boost::dispatch::meta::primitive_of<T>::type
   *                >::type     r;
   * @endcode
   *
   * @par Usage
   *
   * @include behave_as.cpp
   */
  template<class Lambda,class T>
  struct  behave_as
        : boost::mpl::
          apply1< Lambda, typename primitive_of<T>::type >::type
  {};
} } }

#endif
