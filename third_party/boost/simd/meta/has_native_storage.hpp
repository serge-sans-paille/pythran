//==================================================================================================
/*!
  @file

  @copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_META_HAS_NATIVE_STORAGE_HPP_INCLUDED
#define BOOST_SIMD_META_HAS_NATIVE_STORAGE_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/detail/storage_of.hpp>
#include <boost/simd/detail/nsm.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api

    Checks if a type is Vectorizable with native storage

    Evaluates to @c true if a pack of type @c Type with a cardinal of @c N
    is stored using a native SIMD register on current architecture.

    @tparam Type  Type to check
    @tparam N     Cardinal associated to the type check. Defaults to the native cardinal of Type
  **/
  template<typename T, std::size_t N = native_cardinal<T>::value>
  struct  has_native_storage
#if !defined(DOXYGEN_ONLY)
        : nsm::bool_< std::is_same< typename detail::storage_status<T,N,abi_of_t<T,N>>::type
                                  , detail::native_status
                                  >::value
                    >
#endif
  {};
} }

#endif
