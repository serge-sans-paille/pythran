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

#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace dispatch
{
  namespace tt = nsm::type_traits;

  template<typename T> struct pointer_rank : tt::integral_constant<std::size_t,0> {};

  template<typename T>
  struct pointer_rank<T*>  : tt::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};

  template<typename T>
  struct pointer_rank<T* const>  : tt::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};
  template<typename T>
  struct pointer_rank<T* volatile>  : tt::integral_constant<std::size_t,1+pointer_rank<T>::value>
  {};
} }

#endif
