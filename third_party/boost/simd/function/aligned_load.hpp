//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ALIGNED_LOAD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-memory

    Load a value from aligned memory into a generic variable


    @par Header <boost/simd/function/aligned_load.hpp>

    @param ptr Memory to aligned_load from
    @param o   Memory offset

    @return The value stored in said memory block
  **/
  template<typename T, typename Pointer, typename Offset> T aligned_load(Pointer ptr, Offset o) {}

  /*!
    @overload
  */
  template<typename T, typename Pointer> T aligned_load(Pointer ptr) {}

} }
#endif

#include <boost/simd/function/scalar/aligned_load.hpp>
#include <boost/simd/function/simd/aligned_load.hpp>

#endif
