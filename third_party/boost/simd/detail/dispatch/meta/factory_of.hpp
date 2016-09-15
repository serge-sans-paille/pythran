//==================================================================================================
/*!
  @file

  Defines the meta::factory_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_FACTORY_OF_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_FACTORY_OF_HPP_INCLUDED

#include <boost/simd/detail/dispatch/detail/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection

    @brief Recursive meta-model generator

    For any type @c T, returns a template alias able to reconstruct @c T using a different primitive
    type.

    @tparam T     Type to build a type-factory of
    @tparam Limit

    @par Models:

    @metafunction

    @par Semantic:

    For any type @c T:

    @code
    boost::dispatch::factory_of<T>::apply;
    @endcode

    return a template alias so that, for any type @c U:

    @code
    using X = apply<U>;
    @endcode

    generates a type @c X so that:

    @code
    std::is_same<boost::dispatch::primitive_of<X>, U>::value
    @endcode

    and for which the boost::dispatch::model_of template aliases are equivalent.

    Put in another way, boost::dispatch::factory_of is a recursive application of
    boost::dispatch::model_of so that every nested type are traversed during reconstruction.

    @see primitive_of
    @see model_of
  **/
  template<typename T, typename Limit = primitive_of_t<T>>
  struct factory_of : detail::factory_of<T, Limit>
  {};
} }

#endif
