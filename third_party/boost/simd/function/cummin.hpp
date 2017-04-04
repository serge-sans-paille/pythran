//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CUMMIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CUMMIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
    This function object computes the cumulate minimum of the argument elements


    @par Header <boost/simd/function/cummin.hpp>

    @par Example:

      @snippet cummin.cpp cummin

    @par Possible output:

      @snippet cummin.txt cummin

  **/
  Value cummin(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/cummin.hpp>
#include <boost/simd/function/simd/cummin.hpp>

#endif
