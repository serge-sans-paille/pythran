//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_ALLOCATOR_HPP_INCLUDED

#include <boost/align/aligned_allocator.hpp>
#include <boost/align/aligned_delete.hpp>

#include <boost/simd/pack.hpp>

namespace boost { namespace simd
{
  namespace detail
  {
    template< typename T, std::size_t Cardinal
            , bool isArithmetic = std::is_arithmetic<T>::value
            > struct align_of
    {
      static const std::size_t value = boost::simd::pack<T,Cardinal>::alignment;
    };

    template< typename T,std::size_t Cardinal>
    struct align_of<T,Cardinal,false>
    {
      static const std::size_t value = alignof(T);
    };

    template<typename T> struct align_of<T,0ULL,true>
    {
      static const std::size_t value = boost::simd::pack<T>::alignment;
    };

    template<typename T, std::size_t N, typename ABI, std::size_t Cardinal>
    struct align_of<boost::simd::pack<T,N,ABI>, Cardinal, false>
    {
      static const std::size_t card = Cardinal ? Cardinal : N;
      static const std::size_t value = boost::simd::pack<T,card,ABI>::alignment;
    };
  }

  /*!
    @ingroup group-api

    Convenience alias defining a standard compliant allocator returning memory which alignment
    is compatible with the storage of boot::simd::pack<T,Cardinal> or the actual alignment of @c T
    if @c T is not an arithmetic type.

    @tparam T Type of data to be allocated
    @tparam Cardinal Cardinal of the pack to be used in the allocated memory.
                     By default, Cardinal is equal to the expected cardinal for a pack<T>.
  */
  template<typename T, std::size_t Cardinal = 0ULL>
  using allocator = boost::alignment::aligned_allocator<T,detail::align_of<T,Cardinal>::value>;

  using aligned_delete = boost::alignment::aligned_delete;
} }

#endif
