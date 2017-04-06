//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_BITWISE_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_META_IS_BITWISE_LOGICAL_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/config.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace tt = nsm::type_traits;

  /*!
    @ingroup  group-api
    @brief    Checks if type is not scalar

    For a given pack type @c Type, checks if said type

    @tparam Type      Type to check
  **/
  template<typename T>
  struct  is_bitwise_logical
        : tt::integral_constant< bool
                               , sizeof(as_arithmetic_t<T>) == sizeof(as_logical_t<T>)
                               >
  {};

  /*!
    @ingroup  group-api
    @brief Eager short-cut to is_bitwise_logical meta-function
  **/
  template<typename T>
  using is_bitwise_logical_t = typename is_bitwise_logical<T>::type;

} }

#endif
