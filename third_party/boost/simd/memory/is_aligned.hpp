//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_IS_ALIGNED_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_IS_ALIGNED_HPP_INCLUDED

#include <boost/simd/memory/preferred_alignment.hpp>
#include <boost/simd/detail/is_aligned.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd
{
  /*!
    @ingroup group-api
    Checks if a pointer is aligned within current architecture's constraints.

    @param ptr Pointer to check
    @return @c true if @c ptr is aligned properly; @c false otherwise
  **/
  template<typename T>
  BOOST_FORCEINLINE bool is_aligned(T const* ptr) BOOST_NOEXCEPT
  {
    return ::boost::simd::detail::is_aligned(ptr, preferred_alignment<T>::value );
  }

  /*!
    @ingroup group-api
    Checks if a pointer is aligned withing a given architecture's constraints.

    @param ptr  Pointer to check
    @param arch Architecture descriptor to use as reference
    @return @c true if @c ptr is aligned properly; @c false otherwise
  **/
  template<typename T, typename Arch>
  BOOST_FORCEINLINE bool is_aligned(T const* ptr, Arch const& arch) BOOST_NOEXCEPT
  {
    boost::ignore_unused(arch);
    return ::boost::simd::detail::is_aligned(ptr, limits<Arch>::bytes );
  }
} }

#endif
