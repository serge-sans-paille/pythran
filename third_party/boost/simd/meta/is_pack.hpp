//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_PACK_HPP_INCLUDED
#define BOOST_SIMD_META_IS_PACK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;

  /*!
    @ingroup  group-api
    @brief    Checks if type is a pack

    For a given type @c Type, checks if said type is a pack type

    @tparam Type      Type to check
  **/
  template <typename T>
  struct is_pack : nsm::bool_<false> {};

  template <typename T, std::size_t N, typename ABI>
  struct is_pack<pack<T, N, ABI>> : nsm::bool_<true> {};

  /*!
    @ingroup group-api
    Eager short-cut for is_pack_t
  **/
  template <typename T>
  using is_pack_t = typename is_pack<T>::type;

   /*!
    @ingroup  group-api
    @brief    Checks if type is not a pack

    For a given type @c Type, checks if said type is not a pack type

    @tparam Type      Type to check
  **/
  template <typename T>
  struct is_not_pack : nsm::not_<is_pack<T>> {};

  /*!
    @ingroup group-api
    Eager short-cut for is_not_pack_t
  **/
  template <typename T>
  using is_not_pack_t = typename is_not_pack<T>::type;
} }

#endif
