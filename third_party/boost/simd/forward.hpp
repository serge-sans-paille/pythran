//==================================================================================================
/*!
  @file

  Forward declaration of common components

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

**/
//==================================================================================================
#ifndef BOOST_SIMD_FORWARD_HPP_INCLUDED
#define BOOST_SIMD_FORWARD_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/meta/native_cardinal.hpp>
#include <boost/simd/meta/abi_of.hpp>

namespace boost { namespace simd
{
  // Forward declaration of pack
  template< typename T
          , std::size_t N = native_cardinal<T>::value
          , typename ABI  = abi_of_t<T,N>
          >
  class pack;

  // Forward declaration of logical
  template<typename T> struct logical;
} }

#endif
