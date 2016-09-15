//==================================================================================================
/*!
  @file

  Defines the meta::model_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_MODEL_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_MODEL_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/model_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Model generator meta-function

    Defines, for any given type @c T, a @metafunction which can reconstruct a new type @c U similar
    to @c T but by using a different underlying type, all reference and cv-qualifiers being
    discarded.

    @par Models:

    @metafunction

    @par Semantic:

    For any type @c T,

    @code
    std::is_same<boost::mpl::apply<model_of<T>,value_of_t<T>>::type, T>::value
    @endcode

    evaluates to @c true.

    @par Extension Point:

    meta::model_of can be specialized for user-defined types by either overloading or by
    specializing (eventually through SFINAE) the ext::model_of class

    Specialization for value_of are provided for most of standard and Boost types.

    @tparam T Type to turn into a generator @metafunction
  **/
  template<typename T> struct model_of                    : ext::model_of<T>  {};
  template<typename T> struct model_of<T&>                : model_of<T>       {};
  template<typename T> struct model_of<T&&>               : model_of<T>       {};
  template<typename T> struct model_of<T const>           : model_of<T>       {};
  template<typename T> struct model_of<volatile T>        : model_of<T>       {};
  template<typename T> struct model_of<volatile T const>  : model_of<T>       {};
} }

#endif
