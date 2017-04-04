//==================================================================================================
/*!
  @file

  Defines the meta::behave_as meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_BEHAVE_AS_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-introspection
    @brief Apply meta-function to a type's Primitive type

    Apply a meta-function to the Primitive type of its input.

    @tparam T         Type to manipulate
    @tparam Function  Meta-function to apply
  **/
  template<typename T, typename Function>
  struct  behave_as
        : nsm::apply<Function,boost::dispatch::primitive_of_t<T>>
  {};

  template<typename T, typename Function>
  using  behave_as_t = typename behave_as<T,Function>::type;
} }

#endif
