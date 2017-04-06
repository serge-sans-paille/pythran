//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMSUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMSUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
    This function object returns the cumulate sum of the argument elements

    @par Header <boost/simd/function/cumsum.hpp>

    @see cumprod, cummin, cummax

    @par Example:

      @snippet cumsum.cpp cumsum

    @par Possible output:

      @snippet cumsum.txt cumsum

  **/
  Value cumsum(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/cumsum.hpp>
#include <boost/simd/function/simd/cumsum.hpp>

#endif
