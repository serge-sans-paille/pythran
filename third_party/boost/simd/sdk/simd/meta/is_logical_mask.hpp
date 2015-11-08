//==============================================================================
//         Copyright 2003 - 2014 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_META_IS_LOGICAL_MASK_HPP_INCLUDED

#include <boost/simd/sdk/meta/is_bitwise_logical.hpp>
#include <boost/simd/sdk/simd/native_fwd.hpp>
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

// Forward-declare logical
namespace boost { namespace simd
{
  template<class T>
  struct logical;
} }

namespace boost { namespace simd { namespace meta
{
  template<class T>
  struct is_logical_mask
       : mpl::false_
  {
  };

  template<class T, class X>
  struct is_logical_mask< native< logical<T>, X > >
       : is_bitwise_logical<native< logical<T>, X > >
  {
  };

} } }

#endif
