//==================================================================================================
/*!
  @file

  Defines the meta::scalar_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_SCALAR_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_SCALAR_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/scalar_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Compute the basic value type of an arbitrary type

    Retrieves the most embedded fundamental type of any given type, carrying over
    cv-qualifiers.

    @tparam T Type to analyze
  **/
  template<typename T> struct scalar_of           : ext::scalar_of<T> {};
  template<typename T> struct scalar_of<T&>       : ext::scalar_of<T> {};
  template<typename T> struct scalar_of<T const>  : ext::scalar_of<T> {};
  template<typename T> struct scalar_of<T const&> : ext::scalar_of<T> {};
  template<typename T> struct scalar_of<T&&>      : ext::scalar_of<T> {};

  /// Eager shortcut for scalar_of
  template<typename T> using scalar_of_t = typename scalar_of<T>::type;
} }

#endif
