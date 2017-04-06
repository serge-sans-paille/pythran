//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-reduction
     This function object returns the sum of the elements of the SIMD argument

    @see sum


    @par Header <boost/simd/function/sum.hpp>

    @par Example:

      @snippet sum.cpp sum

    @par Possible output:

      @snippet sum.txt sum

  **/
  scalar_of_t<Value> sum(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sum.hpp>
#include <boost/simd/function/simd/sum.hpp>

#endif
