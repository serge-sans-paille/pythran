//==================================================================================================
/*!
  @file

  Defines the as_floating meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_AS_FLOATING_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_AS_FLOATING_HPP_INCLUDED

#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/primitive_of.hpp>
#include <boost/simd/detail/dispatch/meta/make_floating.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace detail
  {
    template<typename T> struct as_floating
    {
      using type  = boost::dispatch::make_floating_t< sizeof(boost::dispatch::primitive_of_t<T>)
                                                    , boost::dispatch::factory_of<T>
                                                    >;
    };
  }

  /*!
    @ingroup group-generation
    @brief Turn a type into an equivalent floating point type

    Converts any type which Primitive is Fundamental into a floating point type with a compatible
    size .

    @tparam T     Type to convert.
  **/
  template<typename T>
  struct as_floating : detail::as_floating<typename std::decay<T>::type>
  {};

  template<typename T>
  using as_floating_t = typename as_floating<T>::type;
} }

#endif
