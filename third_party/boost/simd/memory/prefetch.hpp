//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_PREFETCH_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_PREFETCH_HPP_INCLUDED

#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd
{
  /*!
    @enum prefetch_hints
    @brief Prefecth strategies

    Provides short-cut for the prefetch strategies usable with prefetch_read and
    prefetch_write.

    @see prefetch_read
    @see prefetch_write
  **/
  enum  prefetch_hints
      { non_temporal = 0  /**<  Data are not kept in cache            */
      , low_locality      /**<  Data are kept in few cache levels     */
      , moderate_locality /**<  Data are kept in some cache levels    */
      , high_locality     /**<  Data are kept in all level of caches  */
      };

  /*!
    @brief Prefetch for read operations

    Issue a software prefetch command for next read operations using a
    given strategy for locality.

    @tparam Strategy Hint for locality handling

    @param pointer Memory address to prefetch from

    @see prefetch_hints
  **/
  template<int Strategy>
  BOOST_FORCEINLINE void prefetch_read(void const* pointer)
  {
    #ifdef __GNUC__
    __builtin_prefetch(pointer, 0, Strategy);
    #elif defined( BOOST_SIMD_HAS_SSE_SUPPORT )
    _mm_prefetch( static_cast<char const*>(pointer), Strategy);
    #endif
  }

  /*!
    @brief Prefetch for write operations

    Issue a software prefetch command for next write operations using a
    given strategy for locality.

    @tparam Strategy Hint for locality handling

    @param pointer Memory address to prefetch to

    @see prefetch_hints
  **/
  template<int Strategy>
  BOOST_FORCEINLINE void prefetch_write(void const* pointer)
  {
    #ifdef __GNUC__
    __builtin_prefetch(pointer, 1, Strategy);
    #elif defined( BOOST_SIMD_HAS_SSE_SUPPORT )
    _mm_prefetch( static_cast<char const*>(pointer), Strategy);
    #endif
  }

  /*!
    @brief Prefetch temporary values

    Issue a software prefetch command for next read operations for temporary
    data.

    @param pointer Memory address to prefetch to

    @see prefetch_hints
  **/
  BOOST_FORCEINLINE void prefetch_temporary(void const* pointer)
  {
    prefetch_read<non_temporal>(pointer);
  }
} }

#endif
