//==================================================================================================
/*!
  @file

  Defines the hierarchies associated to sized types

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SIZED_TYPES_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_HIERARCHY_SIZED_TYPES_HPP_INCLUDED

#include <boost/simd/detail/dispatch/hierarchy/integer.hpp>
#include <boost/simd/detail/dispatch/hierarchy/floating.hpp>
#include <boost/simd/detail/dispatch/hierarchy/signed_types.hpp>
#include <boost/simd/detail/dispatch/meta/sign_of.hpp>
#include <boost/simd/detail/dispatch/meta/behave_as.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <climits>
#include <cstddef>

namespace boost { namespace dispatch
{
  /*!
    @ingroup group-tag
    @brief Sized type hierarchy tag

    Types classified as sized_type_ if their sizeof is exactly BitSize.

    @tparam T       Base hierarchy
    @tparam BitSize Type size in bits
  **/
  template<typename T, std::size_t BitSize>
  struct sized_type_ : std::conditional < behave_as<T, std::is_floating_point<nsm::_1>>::value
                                        , floating_<T>
                                        , signed_integral_<T,sign_of_t<T>>
                                        >::type
  {
    static const std::size_t bits = BitSize;
    static const std::size_t byte = bits/CHAR_BIT;

    using parent = typename std::conditional< behave_as<T, std::is_floating_point<nsm::_1>>::value
                                            , floating_<T>
                                            , signed_integral_<T,sign_of_t<T>>
                                            >::type;
  };

  /*!
    @ingroup group-tag
    @brief 8 bits type hierarchy tag

    8 bits types are classified as type8_.

    @tparam T Base hierarchy
  **/
  template<typename T> using type8_ = sized_type_<T,8>;

  /*!
    @ingroup group-tag
    @brief 16 bits type hierarchy tag

    16 bits types are classified as type16_.

    @tparam T Base hierarchy
  **/
  template<typename T> using type16_ = sized_type_<T,16>;

  /*!
    @ingroup group-tag
    @brief 32 bits type hierarchy tag

    32 bits types are classified as type32_.

    @tparam T Base hierarchy
  **/
  template<typename T> using type32_ = sized_type_<T,32>;

  /*!
    @ingroup group-tag
    @brief 64 bits type hierarchy tag

    64 bits types are classified as type64_.

    @tparam T Base hierarchy
  **/
  template<typename T> using type64_ = sized_type_<T,64>;
} }

#endif
