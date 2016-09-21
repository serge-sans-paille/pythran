//==================================================================================================
/*!
  @file

  Defines the pointer_rank meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_DISPATCH_META_POINTER_RANK_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_DISPATCH_META_POINTER_RANK_HPP_INCLUDED

#include <type_traits>

namespace boost { namespace dispatch
{
  template<typename T> struct pointer_rank : std::integral_constant<std::size_t,0> {};

  template<typename T>
  struct pointer_rank<T*>  : std::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};

  template<typename T>
  struct pointer_rank<T* const>  : std::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};
  template<typename T>
  struct pointer_rank<T* volatile>  : std::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};
} }

#endif
