//==================================================================================================
/*!
  @file
  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_META_AS_PACK_HPP_INCLUDED
#define BOOST_SIMD_META_AS_PACK_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  namespace ext
  {
    template< typename T, std::size_t N> struct as_pack
    {
      using type = pack<T,N>;
    };
  }

  /*!
    @ingroup  group-api
    Extension point for pack-liek type generation

    @tparam Type  Base type
    @tparam N     Expected cardinal
  **/
  template< typename T, std::size_t N = pack<T>::static_size>
  struct as_pack : ext::as_pack<T,N> {};

  template< typename T, std::size_t N = pack<T>::static_size >
  using as_pack_t = typename as_pack<T, N>::type;
} }

#endif
