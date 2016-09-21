//==================================================================================================
/*!
  @file

  Defines the meta::primitive_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_PRIMITIVE_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_PRIMITIVE_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/primitive_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Primitive type computation

    For any given type @c T, returns the primitive type, i.e the most underlying type of @c T.

    @tparam Type to extract a primitive from.

    @par Models:

    @metafunction

    @par Semantic:
    For a given type T,

    @code
    using type = boost::dispatch::primitive_of<T>;
    @endcode

    is defined so that :

    @code
    std::is_same<type, boost::dispatch::value_of_t<type>>::value
    @endcode

    evaluates to @c true.

    Put in another way, primitive_of is a recursive application of value_of so
    that every nested type are traversed to find the most underlying type of @c T.

    @see value_of
    @see model_of
  **/
  template<typename T>
  struct primitive_of : detail::primitive_of<boost::dispatch::value_of_t<T>, T>
  {};

  template<typename T> using primitive_of_t = typename primitive_of<T>::type;
} }

#endif
