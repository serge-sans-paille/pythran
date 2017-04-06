//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMMAX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMMAX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
    This function object computes the cumulate maximum of the argument elements


    @par Header <boost/simd/function/cummax.hpp>

    @par Example:

      @snippet cummax.cpp cummax

    @par Possible output:

      @snippet cummax.txt cummax

  **/
  Value cummax(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/cummax.hpp>
#include <boost/simd/function/simd/cummax.hpp>

#endif
