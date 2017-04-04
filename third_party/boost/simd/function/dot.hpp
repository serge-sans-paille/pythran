//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_DOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_DOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
    This function object returns the returns the dot product of the two arguments


    @par Header <boost/simd/function/dot.hpp>

    @par Example:

      @snippet edot.cpp dot

    @par Possible output:

      @snippet edot.txt dot

  **/
  scalar_of_t<Value> dot(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/dot.hpp>
#include <boost/simd/function/simd/dot.hpp>

#endif
