//==================================================================================================
/*!
  @file

  Defines the value_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_VALUE_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_VALUE_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/config.hpp>

namespace boost { namespace dispatch
{
  namespace ext
  {
    template<typename T, typename Enable = void> struct value_of;
    template<typename T, typename Enable = void> struct value_of_cv;
  }

  /*!
    @ingroup group-introspection
    @brief Underlying type evaluation

    Evaluates, for any given type @c T, the underlying type of @c T.

    @par Models:

    @metafunction

    @par Semantic:

    For any type @c T,

    @code
    using U = value_of<T>;
    @endcode

    is defined so that

    @code
    std::is_same<T, meta::model_of<T>::type<U>>::type
    @endcode

    evaluates to @true_ .

    @par Extension Point:

    meta::value_of can be specialized for user-defined types by either overloading or specializing
    (eventually through SFINAE) the ext::value_of and/or ext::value_of_cv classes

    Specialization for value_of are provided for most of standard and Boost types.

    @tparam T Type to analyze
  **/
  template<typename T> struct  value_of          : ext::value_of<T>          {};

  template<typename T> struct  value_of<T&>      : ext::value_of_cv<T&>      {};
  template<typename T> struct  value_of<T&&>     : ext::value_of_cv<T&&>     {};
  template<typename T> struct  value_of<T const> : ext::value_of_cv<T const> {};

#ifndef BOOST_NO_RESTRICT_REFERENCES
  template<typename T> struct  value_of<T& BOOST_RESTRICT> : ext::value_of_cv<T&> {};
#endif

  // Eager short-cut for value_of
  template<typename T> using value_of_t = typename value_of<T>::type;
} }

#include <boost/simd/detail/dispatch/detail/value_of.hpp>

#endif
