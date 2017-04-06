//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAXIMUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAXIMUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-reduction
   This function object returns the greatest element of the argument

    @par Header <boost/simd/function/maximum.hpp>

    @see minimum

    @par Example:

      @snippet maximum.cpp maximum

    @par Possible output:

      @snippet maximum.txt maximum

  **/
  scalar_of_t<Value> maximum(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/maximum.hpp>
#include <boost/simd/function/simd/maximum.hpp>

#endif
