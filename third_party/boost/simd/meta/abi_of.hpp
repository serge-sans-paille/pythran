//==================================================================================================
/*!
  @file

  Defines the abi_of meta-function

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_META_ABI_OF_HPP_INCLUDED
#define BOOST_SIMD_META_ABI_OF_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/arch/spec.hpp>

namespace boost { namespace simd
{
  template<typename T> struct logical;

  /*!
    @ingroup  group-api
    @brief    Type/Size to ABI mapping

    For a given @c Type and width @c N, returns a type uniquely identifying the SIMD ABI used to
    handle such type/size combination.

    @tparam Type Type to store
    @tparam N    Number of elements to store
  **/
  template<typename Type, std::size_t N> struct abi_of                  : ext::abi_of<Type,N> {};
  template<typename Type, std::size_t N> struct abi_of<logical<Type>,N> : ext::abi_of<Type,N> {};

  /// @brief Eager short-cut to abi_of
  template<typename Type, std::size_t N> using abi_of_t = typename abi_of<Type,N>::type;
} }

#endif


