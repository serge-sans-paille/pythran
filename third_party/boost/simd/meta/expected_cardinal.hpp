//==================================================================================================
/*!
  @file

  Defines the expected_cardinal metafunction

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_EXPECTED_CARDINAL_HPP_INCLUDED
#define BOOST_SIMD_META_EXPECTED_CARDINAL_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/arch/limits.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  namespace tt = nsm::type_traits;

  template<typename T> struct logical;

  /*!
    @ingroup group-api
    @brief Expected cardinal of register

    Computes the cardinal a potential SIMD register containing elements of type @c Type on
    extension @c Extension.

    @tparam Type      Element type of the expected register
    @tparam Extension SIMD Extension tag
  **/
  template<typename Type, typename Extension>
  struct  expected_cardinal
        : tt::integral_constant<std::size_t,limits<Extension>::bytes/sizeof(Type)>
  {};

  template<typename Type, typename Extension>
  struct  expected_cardinal<logical<Type>,Extension>
        : tt::integral_constant<std::size_t,limits<Extension>::bytes/sizeof(Type)>
  {};
} }

#endif
