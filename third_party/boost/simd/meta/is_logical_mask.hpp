//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED
#define BOOST_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

/*!
  @brief Is a SIMD vector both bitwise_logical and contain either all 0 or ~0.

  This metafunction represents a subset of is_bitwise_logical and returns true
  if the same SIMD registers are used by both arithmetic and logical vectors and
  if logical vectors are represented by either all 0 or ~0. This is assumed to be
  true - otherwise overloads must be provided on architectures where logical types
  are bitwise_logical but do not contain either all 0 or ~0 - for example qpx.

  @par semantic
   boost::simd::meta::is_logical_mask<T>::value = true/false

  @param T - a SIMD register on the target architecture
*/

  template<typename T > struct is_logical_mask : is_bitwise_logical<T> {};
} }

#endif
