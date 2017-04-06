//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the high part of the entry
    as an unsigned integer of the size of
    the input.

    @par Header <boost/simd/function/hi.hpp>

    @see  lo

    @par Example:

      @snippet hi.cpp hi

    @par Possible output:

      @snippet hi.txt hi

  **/
  as_integer_t<Value, unsigned> hi(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/hi.hpp>
#include <boost/simd/function/simd/hi.hpp>

#endif
