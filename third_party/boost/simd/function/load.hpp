//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOAD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOAD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-memory

    Load a value from memory into a generic variable


    @par Header <boost/simd/function/load.hpp>

    @param ptr Memory to load from
    @param o   Memory offset

    @return The absolute value of the parameter.
  **/
  template<typename T, typename Pointer, typename Offset> T load(Pointer ptr, Offset o);

  /*!
    @overload
  **/
  template<typename T, typename Pointer> T load(Pointer ptr);

} }
#endif

#include <boost/simd/function/scalar/load.hpp>
#include <boost/simd/function/simd/load.hpp>

#endif
