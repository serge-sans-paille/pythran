//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_AS_ARITHMETIC_HPP_INCLUDED
#define BOOST_SIMD_META_AS_ARITHMETIC_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  namespace detail
  {
    template<typename T, typename F>
    struct as_arithmetic_impl
    {
      using type = nsm::apply<F, T>;
    };

    template<typename T, typename F>
    struct as_arithmetic_impl< logical<T>, F >
    {
      using type = nsm::apply<F, T>;
    };
  }

  template<typename T>
  struct  as_arithmetic
        : detail::as_arithmetic_impl< dispatch::scalar_of_t<T>
                                    , dispatch::factory_of<T, dispatch::scalar_of_t<T>>
                                    >
  {};

  template<typename T>
  using as_arithmetic_t = typename as_arithmetic<T>::type;
} }

#endif
