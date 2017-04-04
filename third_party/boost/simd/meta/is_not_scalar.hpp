//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_NOT_SCALAR_HPP_INCLUDED
#define BOOST_SIMD_META_IS_NOT_SCALAR_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/is_scalar.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy/scalar.hpp>
#include <boost/simd/detail/dispatch/models.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;

  /*!
    @ingroup  group-api
    @brief    Checks if type is not scalar

    For a given type @c Type, checks if said type is not a scalar type, i.e a type stored in a
    hardware wide register.

    @tparam Type      Type to check
  **/
  template<typename T>
  struct is_not_scalar : nsm::not_ < is_scalar < T>>
  {};
  template<typename T>
  using is_not_scalar_t = typename is_not_scalar<T>::type;
} }

#endif
