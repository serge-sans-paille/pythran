//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_META_AS_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_META_AS_LOGICAL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/logical.hpp>
#include <boost/simd/meta/real_of.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/meta/factory_of.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    template<typename T, typename F>
    struct  as_logical
    {
      using type = nsm::apply<F, logical<T> >;
    };

    template<typename T, typename F>
    struct  as_logical< logical<T>, F >
    {
      using type = nsm::apply<F, logical<T> >;
    };

    template<typename F>
    struct  as_logical<bool, F>
    {
      using type = nsm::apply<F, bool >;
    };
  }

  /*!
    @ingroup  group-api
    @brief    Convert type to its logical type counterpart

    For a given type @c T , provides a type of same structure but able to store a logical value.
    Provisions are taken so that conversion of logical and @c bool types is idempotent.

    @tparam T Type to convert
  **/
  template<typename T>
  struct  as_logical
        : detail::as_logical< real_of_t<T>
                            , dispatch::factory_of<T,dispatch::scalar_of_t<T>>
                            >
  {
  };

  /*!
    @ingroup  group-api
    @brief Eager short-cut to the as_logical meta-function

    @tparam T Type to convert
  **/
  template<typename T> using as_logical_t = typename as_logical<T>::type;
} }

#endif
