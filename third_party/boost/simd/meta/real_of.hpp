//==================================================================================================
/*!
  @file

  Defines the as_logical meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_REAL_OF_HPP_INCLUDED
#define BOOST_SIMD_META_REAL_OF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup  group-api
    @brief    Compute the underlying real type of a given type

    For any given type @c T , computes a scalar underlying type which can represent a value
    from \f$\mathbb{R}\f$.

    @tparam T      Type to convert
  **/
  template<typename T>
  struct real_of : boost::dispatch::scalar_of<T>
  {};

  /*!
    @ingroup  group-api
    @brief Eager short-cut to real_of meta-function
  **/
  template<typename T> using real_of_t = typename real_of<T>::type;
} }

#endif
