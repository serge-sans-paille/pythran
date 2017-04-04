//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_SCALAR_HPP_INCLUDED
#define BOOST_SIMD_META_IS_SCALAR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/dispatch/hierarchy/unspecified.hpp>
#include <boost/simd/detail/dispatch/hierarchy/scalar.hpp>
#include <boost/simd/detail/dispatch/models.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;

  /*!
    @ingroup  group-api
    @brief    Checks if type is scalar

    For a given type @c Type, checks if said type is a scalar type, i.e not a type stored in a
    hardware wide register.

    @tparam Type      Type to check
  **/
  template<typename T>
  struct is_scalar : bd::models_t<T, bd::scalar_<bd::unspecified_<nsm::_1>> >
  {};
  template<typename T>
  using is_scalar_t = typename is_scalar<T>::type;
} }

#endif
