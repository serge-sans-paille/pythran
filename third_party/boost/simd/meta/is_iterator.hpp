//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_ITERATOR_HPP_INCLUDED
#define BOOST_SIMD_META_IS_ITERATOR_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <type_traits>

namespace boost { namespace simd
{
  namespace detail
  {
    template <typename T> struct is_iterator_impl
    {
      static std::false_type test(...);

      template <  typename U
                , typename=typename std::iterator_traits<U>::difference_type
                , typename=typename std::iterator_traits<U>::pointer
                , typename=typename std::iterator_traits<U>::reference
                , typename=typename std::iterator_traits<U>::value_type
                , typename=typename std::iterator_traits<U>::iterator_category
                > static std::true_type test(U&&);

      static const bool value = std::is_same< decltype(test(std::declval<T>()))
                                            , std::true_type
                                            >::value;
    };
  }

  /*!
    @ingroup  group-api
    @brief    Checks if type is iterator

    For a given type @c Type, checks if said type is a iterator type.

    @tparam Type      Type to check
  **/
  template<typename T>
  struct is_iterator : std::integral_constant<bool, detail::is_iterator_impl<T>::value>
  {};

  template<typename T>
  using is_iterator_t = typename is_iterator<T>::type;
} }

#endif
